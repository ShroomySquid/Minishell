/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/07 10:07:53 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_name_length(int *i, int *a, char *buff, t_env *env)
{
	t_env	*cur_node;
	int		b;

	b = 0;
	cur_node = env;
	while (buff[*i + b] && is_white_space(buff[*i + b]) == 0)
		b++;
	while (cur_node->name)
	{
		if (!ft_strncmp(&buff[*i + 1], cur_node->name, b - 1))
		{
			*i += b;
			b = 0;
			while (cur_node->value[b])
				b++;
			*a += b;
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

int tb_length_env(char *buff, t_env *env)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		if ('\'' == buff[i])
			to_end_quote_length(buff[i], buff, &i, &a);
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

void replace_name(char *temp_buff, t_env *cur_node, int *b, int *a)
{
	temp_buff[*a] = cur_node->value[*b];
	*a += 1;
	*b += 1;
}

void get_name(char *buff, char *temp_buff, int *i, int *a, t_env *env)
{
	int b;
	t_env *cur_node;

	b = 0;
	cur_node = env;
	while (buff[*i + b] && is_white_space(buff[*i + b]) == 0)
		b++;
	while (cur_node->name)
	{
		if (!ft_strncmp(&buff[*i + 1], cur_node->name, b - 1))
		{
			*i += b;
			b = 0;
			while (cur_node->value[b])
				replace_name(temp_buff, cur_node, &b, a);
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

char *parse_env_var(char *buff, t_env *env)
{
	char *temp_buff;
	int i;
	int a;
	
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
			get_name(buff, temp_buff, &i, &a, env);
		else
		{
			temp_buff[a] = buff[i];
			i++;
			a++;
		}
	}
	temp_buff[a] = '\0';
	free (buff);
	return (temp_buff);
}
