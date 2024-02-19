/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 10:31:23 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_quotes(char ***line, t_exec_st *exec_st)
{
	int		i;
	int		a;
	char	*temp_arg;

	i = 0;
	while (*line && line[0][i])
	{
		a = 1;
		if (check_operators(exec_st, line[0][i]))
		{
			temp_arg = ft_strdup(line[0][i]);
			free(line[0][i]);
			line[0][i] = ft_calloc(ft_strlen(temp_arg) + 1, sizeof(char));
			if (!line[0][i])
				break ;
			while (temp_arg[a] && temp_arg[a] != 34 && temp_arg[a] != 39)
			{
				line[0][i][a - 1] = temp_arg[a];
				a++;
			}
			line[0][i][a] = '\0';
		}
		i++;
	}
}

int	new_length(const char *arg, int i, int a)
{
	char	quote;

	while (arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
		{
			quote = arg[i];
			i++;
			while (arg[i] && arg[i] != quote)
			{
				i++;
				a++;
			}
			if (arg[i])
				i++;
		}
		else if (arg[i])
		{
			i++;
			a++;
		}
	}
	return (a);
}

void	remove_a_quote(const char *arg, int *i, int *a, char *new_arg)
{
	char	quote;

	quote = arg[*i];
	*i += 1;
	while (arg[*i] && arg[*i] != quote)
	{
		new_arg[*a] = arg[*i];
		*i += 1;
		*a += 1;
	}
	if (arg[*i] == quote)
		*i += 1;
}

char	*remove_quote_arg(char *arg)
{
	char	*new_arg;
	int		a;
	int		i;

	i = 0;
	a = 0;
	new_arg = ft_calloc((new_length(arg, i, a) + 1), sizeof(char));
	if (!new_arg)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
			remove_a_quote(arg, &i, &a, new_arg);
		else if (arg[i])
		{
			new_arg[a] = arg[i];
			i++;
			a++;
		}
	}
	new_arg[a] = 0;
	free(arg);
	return (new_arg);
}

int	remove_quotes(char **temp_line, t_exec_st *exec_st)
{
	int	i;

	i = 0;
	while (temp_line[i])
	{
		if (check_operators(exec_st, temp_line[i]))
		{
			i++;
			continue ;
		}
		if (ft_strchr(temp_line[i], 34) || ft_strchr(temp_line[i], 39))
		{
			temp_line[i] = remove_quote_arg(temp_line[i]);
			if (!temp_line[i])
				return (1);
		}
		i++;
	}
	return (0);
}
