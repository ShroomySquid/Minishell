/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:06:19 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 12:12:00 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_sub_array(char **array, int start, int end)
{
	char	**sub_array;
	int		i;

	i = 0;
	if (start >= end)
		return (NULL);
	sub_array = ft_calloc(end - start + 1, sizeof(char *));
	if (!sub_array)
	{
		perror("malloc faild for: sub_array");
		return (NULL);
	}
	while (array[start + i] && (start + i) <= end)
	{
		sub_array[i] = ft_strdup(array[start + i]);
		i++;
	}
	sub_array[i] = 0;
	return (sub_array);
}

int	is_white_space(char c)
{
	if ((c < 14 && c > 8) || c == 32)
		return (1);
	return (0);
}

int	get_exit_code_length(t_env_parse *parse, t_exec_st *exec_st)
{
	int	temp_ret;

	parse->i += 2;
	parse->a += 1;
	temp_ret = exec_st->ret;
	temp_ret = temp_ret / 10;
	while (temp_ret)
	{
		parse->a += 1;
		temp_ret = temp_ret / 10;
	}
	return (0);
}

int	get_exit_code(t_env_parse *parse, t_exec_st *exec_st, char *temp_buff)
{
	char	*ret_str;
	int		ret_len;

	ret_len = 0;
	parse->i += 2;
	ret_str = ft_itoa(exec_st->ret);
	while (ret_str[ret_len])
	{
		temp_buff[parse->a] = ret_str[ret_len];
		ret_len++;
		parse->a += 1;
	}
	free(ret_str);
	return (0);
}

void	to_end_quote(const char *buff, char *temp_buff, int *i, const int a)
{
	char	quote;

	quote = buff[*i];
	temp_buff[*i + a] = buff[*i];
	*i += 1;
	while (buff[*i] && buff[*i] != quote)
	{
		temp_buff[*i + a] = buff[*i];
		*i += 1;
	}
	if (buff[*i])
	{
		temp_buff[*i + a] = buff[*i];
		*i += 1;
	}
}
