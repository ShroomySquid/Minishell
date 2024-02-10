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

int	handle_edge_case(int b, int *i, int *a, char *buff, char *temp_buff)
{
	if (b == 0)
	{
		if (!buff[*i + 1] || is_white_space(buff[*i + 1])
			|| buff[*i + 1] == buff[*i - 1])
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
	int	len;

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
	char	*name;

	b = 0;
	while (buff[*i + b] && is_valid_env_char(buff[*i + b + 1]))
		b++;
	if (handle_edge_case(b, i, a, buff, temp_buff))
		return ;
	name = ft_substr(&buff[*i + 1], 0, b);
	if (!name)
		return ;
	cur_node = env_find(env, name);
	if (cur_node)
		replace_name(temp_buff, cur_node, a);
	free(name);
	*i += b + 1;
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
			env_next(&i, &a, temp_buff, buff);
	}
	temp_buff[a] = '\0';
	free (buff);
	return (temp_buff);
}
