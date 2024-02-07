/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/06 19:26:00 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int tb_length_env(char *buff, t_env *env)
{
	int i;
	int a;
	int b;
	t_env *cur_node;

	i = 0;
	a = 0;
	while (buff[i])
	{
		b = 0;
		if ('\'' == buff[i])
			to_end_quote_length(buff[i], buff, &i, &a);
		if (buff[i] && (buff[i] == '$' && !is_white_space(buff[i + 1])))
		{
			cur_node = env;
			while (buff[i + b] && !is_white_space(buff[i + b]))
				b++;
			while (cur_node->name)
			{
				if (!ft_strncmp(&buff[i + 1], cur_node->name, b - 1))
				{
					i += b;
					b = 0;
					while (cur_node->value[b])
						b++;
					a += b;
					break ;
				}
				else if (cur_node->next)
					cur_node = cur_node->next;
				else
				{
					i += b;
					break ;
				}
			}
		}
		else
		{
			i++;
			a++;
		}
	}
	a++;
	return (a);
}

char *parse_env_var(char *buff, t_env *env)
{
	char *temp_buff;
	int i;
	int a;
	int b;
	t_env *cur_node;
	
	temp_buff = ft_calloc(tb_length_env(buff, env), sizeof(char));
	if (!temp_buff)
		return (NULL);
	i = 0;
	a = 0;
	while (buff[i])
	{
		if ('\'' == buff[i])
			to_end_quote(buff[i], buff, temp_buff, &i, &a);
		if (buff[i] && buff[i] == '$' && !is_white_space(buff[i + 1]))
		{
			b = 0;
			cur_node = env;
			while (buff[i + b] && !is_white_space(buff[i + b]))
				b++;
			while (cur_node->name)
			{
				if (!ft_strncmp(&buff[i + 1], cur_node->name, b - 1))
				{
					i += b;
					b = 0;
					while (cur_node->value[b])
					{
						temp_buff[a] = cur_node->value[b];
						a++;
						b++;
					}
					break ;
				}
				else if (cur_node->next)
					cur_node = cur_node->next;
				else
				{
					i += b;
					break ;
				}
			}
		}
		else
			temp_buff[a] = buff[i];
		i++;
		a++;
	}
	temp_buff[a] = '\0';
	free (buff);
	return (temp_buff);
}
