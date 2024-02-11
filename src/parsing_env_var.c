/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/11 09:57:29 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_edge_case(t_env_parse *parse, char *buff, char *temp_buff)
{
	if (parse->len == 0)
	{
		if (!buff[parse->i + 1] || is_white_space(buff[parse->i + 1])
			|| buff[parse->i + 1] == buff[parse->i - 1])
		{
			temp_buff[parse->a] = buff[parse->i];
			parse->a += 1;
		}
		parse->i += 1;
		return (1);
	}
	if (!ft_strncmp(&buff[parse->i + 1], "PWD", parse->len - 1))
	{
		get_pwd(temp_buff, &parse->a);
		parse->i += parse->len + 1;
		return (1);
	}
	return (0);
}

void	replace_name(char *temp_buff, t_env *cur_node, t_env_parse *parse)
{
	int	len;

	len = 0;
	while (cur_node->value[len])
	{
		temp_buff[parse->a] = cur_node->value[len];
		parse->a += 1;
		len += 1;
	}
}

void	get_name(char *buff, char *temp_buff, t_env_parse *parse, t_env *env)
{
	t_env	*cur_node;
	char	*name;

	parse->len = 0;
	while (buff[parse->i + parse->len]
		&& is_valid_env_char(buff[parse->i + parse->len + 1]))
		parse->len++;
	if (handle_edge_case(parse, buff, temp_buff))
		return ;
	name = ft_substr(&buff[parse->i + 1], 0, parse->len);
	if (!name)
		return ;
	cur_node = env_find(env, name);
	if (cur_node)
		replace_name(temp_buff, cur_node, parse);
	free(name);
	parse->i += parse->len + 1;
}

char	*parse_env_var(char *buff, t_env *env, t_exec_st *exec_st)
{
	char		*temp_buff;
	t_env_parse	*par;

	par = ft_calloc(sizeof(t_env_parse), 1);
	if (!par)
		return (NULL);
	temp_buff = ft_calloc(tb_len_env(buff, env, exec_st, par), sizeof(char));
	if (!temp_buff)
		return (NULL);
	par->i = 0;
	par->a = 0;
	while (buff[par->i])
	{
		if ('\'' == buff[par->i])
			to_end_quote_var(buff, temp_buff, par);
		if (buff[par->i] && buff[par->i] == '$' && buff[par->i + 1] == '?')
			get_exit_code(par, exec_st, temp_buff);
		if (buff[par->i] && buff[par->i] == '$'
			&& !is_white_space(buff[par->i + 1]))
			get_name(buff, temp_buff, par, env);
		else
			env_next(par, temp_buff, buff);
	}
	temp_buff[par->a] = '\0';
	return (free(buff), free(par), temp_buff);
}
