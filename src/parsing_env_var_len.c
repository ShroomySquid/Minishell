/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/26 15:45:59 by fbarrett         ###   ########.fr       */
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

int	handle_edge_case_len(t_env_parse *parse, char *buff)
{
	if (parse->len == 0)
	{
		if (!buff[parse->i + 1] || is_white_space(buff[parse->i + 1])
			|| buff[parse->i + 1] == 34 || 39 == buff[parse->i + 1])
			parse->a += 1;
		parse->i += 1;
		return (1);
	}
	if (parse->len == 4 && !ft_strncmp(&buff[parse->i], "$PWD", parse->len + 1))
	{
		parse->a += get_pwd_length();
		parse->i += parse->len;
		return (1);
	}
	return (0);
}

int	get_env_name_len(t_env_parse *parse, t_env *cur_node)
{
	parse->i += parse->len;
	parse->len = 0;
	while (cur_node->value[parse->len])
		parse->len += 1;
	parse->a += parse->len;
	return (1);
}

void	get_name_length(t_env_parse *parse, char *buff, t_env *env)
{
	char	*name;

	parse->len = 0;
	while (buff[parse->i + parse->len]
		&& is_valid_env_char(buff[parse->i + parse->len + 1]))
		parse->len++;
	if (handle_edge_case_len(parse, buff))
		return ;
	name = ft_calloc(parse->len + 1, sizeof(char));
	if (!name)
		return ;
	ft_strlcpy(name, &buff[parse->i + 1], parse->len + 1);
	env = env_find(env, name);
	if (env)
		get_env_name_len(parse, env);
	free(name);
}

int	tb_len_env(char *buff, t_env *env,
	t_exec_st *exec_st, t_env_parse *parse)
{
	parse->i = 0;
	parse->a = 0;
	while (buff[parse->i])
	{
		if ('\'' == buff[parse->i])
			to_end_quote_length(buff[parse->i], buff, &parse->i, &parse->a);
		if (buff[parse->i] && buff[parse->i]
			== '$' && buff[parse->i + 1] == '?')
			get_exit_code_length(parse, exec_st);
		if (buff[parse->i] && buff[parse->i]
			== '$' && buff[parse->i + 1] == '$')
			parse->i++;
		else if (buff[parse->i] && buff[parse->i]
			== '$' && !is_white_space(buff[parse->i + 1]))
			get_name_length(parse, buff, env);
		if (buff[parse->i])
		{
			parse->i++;
			parse->a++;
		}
	}
	parse->a += 2;
	return (parse->a);
}
