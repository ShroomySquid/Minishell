/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/08 14:32:50 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_end_quote_var(const char *buff, char *temp_buff, int *i, int *a)
{
	char	quote;

	quote = buff[*i];
	temp_buff[*a] = buff[*i];
	*i += 1;
	*a += 1;
	while (buff[*i] && buff[*i] != quote)
	{
		temp_buff[*a] = buff[*i];
		*i += 1;
		*a += 1;
	}
	if (buff[*i])
	{
		temp_buff[*a] = buff[*i];
		*i += 1;
		*a += 1;
	}
}

int is_valid_env_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

int get_pwd(char *temp_buff, int *a)
{
	char *pwd;
	int i;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	while (pwd[i])
	{
		temp_buff[*a] = pwd[i];
		i++;
		*a += 1;
	}
	free(pwd);
	return (i);
}

int handle_edge_case(int b, int *i, int *a, char *buff, char *temp_buff)
{
	if (b == 0)
	{
		if (!buff[*i + 1] || is_white_space(buff[*i + 1]) || buff[*i + 1] == buff[*i - 1])
		{
			temp_buff[*a] = buff[*i];
			*a += 1;
		}
		*i += 1;
		return (1);
	}
	if (!ft_strncmp(&buff[*i + 1], "PWD", b - 1))
	{
		get_pwd(temp_buff, a);
		*i += b + 1;
		return (1);
	}
	return (0);
}

void	replace_name(char *temp_buff, t_env *cur_node, int *a)
{
	int len;

	len = 0;
	while (cur_node->value[len])
	{
		temp_buff[*a] = cur_node->value[len];
		*a += 1;
		len += 1;
	}
}

void	get_name(char *buff, char *temp_buff, int *i, int *a, t_env *env)
{
	int		b;
	t_env	*cur_node;

	b = 0;
	cur_node = env;
	while (buff[*i + b] && is_valid_env_char(buff[*i + b + 1]))
		b++;
	if (handle_edge_case(b, i, a, buff, temp_buff))
		return ;
	while (cur_node->name)
	{
		//printf("%s len: %d, b len: %d\n", cur_node->name, (int)ft_strlen(cur_node->name), b);
		if (((int)ft_strlen(cur_node->name) == (b)) && !ft_strncmp(&buff[*i + 1], cur_node->name, b - 1))
		{
			printf("hello\n");
			*i += b + 1;
			replace_name(temp_buff, cur_node, a);
			break ;
		}
		else if (cur_node->next)
			cur_node = cur_node->next;
		else
		{
			*i += b + 1;
			break ;
		}
	}
}

int next(int *i, int *a, char *temp_buff, char *buff)
{
	temp_buff[*a] = buff[*i];
	*i += 1;
	*a += 1;
	return (0);
}

char	*parse_env_var(char *buff, t_env *env, t_exec_st *exec_st)
{
	char	*temp_buff;
	int		i;
	int		a;

	temp_buff = ft_calloc(tb_length_env(buff, env, exec_st), sizeof(char));
	if (!temp_buff)
		return (NULL);
	i = 0;
	a = 0;
	while (buff[i])
	{
		if ('\'' == buff[i])
			to_end_quote_var(buff, temp_buff, &i, &a);
		if (buff[i] && buff[i] == '$' && buff[i + 1] == '?')
			get_exit_code(&i, &a, exec_st, temp_buff);
		if (buff[i] && buff[i] == '$' && !is_white_space(buff[i + 1]))
			get_name(buff, temp_buff, &i, &a, env);
		else
			next(&i, &a, temp_buff, buff);
	}
	temp_buff[a] = '\0';
	free (buff);
	return (temp_buff);
}
