/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:06:19 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/11 10:46:08 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_array(char **array_str)
{
	int	i;

	i = 0;
	while (array_str[i])
	{
		ft_printf("%s\n", array_str[i]);
		i++;
	}
}

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

int	get_exit_code_length(int *i, int *a, t_exec_st *exec_st)
{
	int	temp_ret;

	*i += 2;
	*a += 1;
	temp_ret = exec_st->ret;
	temp_ret = temp_ret / 10;
	while (temp_ret)
	{
		*a += 1;
		temp_ret = temp_ret / 10;
	}
	return (0);
}

int	get_exit_code(int *i, int *a, t_exec_st *exec_st, char *temp_buff)
{
	char	*ret_str;
	int		ret_len;

	ret_len = 0;
	*i += 2;
	ret_str = ft_itoa(exec_st->ret);
	while (ret_str[ret_len])
	{
		temp_buff[*a] = ret_str[ret_len];
		ret_len++;
		*a += 1;
	}
	free(ret_str);
	return (0);
}
