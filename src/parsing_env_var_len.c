/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/09 13:16:56 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd_length(void)
{
	char		*pwd;
	size_t		i;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	i = ft_strlen(pwd);
	free(pwd);
	return ((int) i);
}

int	handle_edge_case_len(int b, int *i, int *a, char *buff)
{
	if (b == 0)
	{
		if (!buff[*i + 1] || is_white_space(buff[*i + 1])
			|| buff[*i + 1] == buff[*i - 1])
			*a += 1;
		*i += 1;
		return (1);
	}
	if (!ft_strncmp(&buff[*i], "$PWD", b))
	{
		*a += get_pwd_length();
		*i += b;
		return (1);
	}
	return (0);
}

int	get_env_name_len(int *i, int *a, int *b, t_env *cur_node)
{
	*i += *b;
	*b = 0;
	while (cur_node->value[*b])
		*b += 1;
	*a += *b;
	return (1);
}

void	get_name_length(int *i, int *a, char *buff, t_env *env)
{
	t_env	*cur_node;
	int		b;

	b = 0;
	cur_node = env;
	while (buff[*i + b] && is_valid_env_char(buff[*i + b + 1]))
		b++;
	if (handle_edge_case_len(b, i, a, buff))
		return ;
	while (cur_node->name)
	{
		if ((int)ft_strlen(cur_node->name) > b - 1
			&& !ft_strncmp(&buff[*i + 1], cur_node->name, b - 1))
		{
			get_env_name_len(i, a, &b, cur_node);
			break ;
		}
		else if (cur_node->next)
			cur_node = cur_node->next;
		else
		{
			*i += b;
			break ;
		}
	}
}

int	tb_length_env(char *buff, t_env *env, t_exec_st *exec_st)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		if ('\'' == buff[i])
			to_end_quote_length(buff[i], buff, &i, &a);
		if (buff[i] && buff[i] == '$' && buff[i + 1] == '?')
			get_exit_code_length(&i, &a, exec_st);
		if (buff[i] && buff[i] == '$' && !is_white_space(buff[i + 1]))
			get_name_length(&i, &a, buff, env);
		else
		{
			i++;
			a++;
		}
	}
	a++;
	return (a);
}
