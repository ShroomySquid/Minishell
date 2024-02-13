/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:37:14 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 17:34:03 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_pipe_error(char **line, int i)
{
	char	*error;

	error = ft_strdup("|");
	if (!i)
		return (error);
	if (is_redirect(line, i - 1))
		return (error);
	free(error);
	return (NULL);
}

char	*check_redir_error(char **line, int i)
{
	char	*error;

	error = ft_strdup(line[i]);
	if (!line[i + 1])
		return (error);
	if (is_redirect(line, i + 1))
		return (error);
	free(error);
	return (NULL);
}

char	*error_return(char *token)
{
	char	*error;

	error = ft_strdup(token);
	return (error);
}

char	*parse_errors(char *buff)
{
	int	i;
	int	a;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i])
	{
		a = 0;
		while (buff[i + a] && 34 != buff[i + a] && 39 != buff[i + a])
			a++;
		if (ft_strnstr(&buff[i], "<<<", a))
			return (error_return("<<"));
		if (ft_strnstr(&buff[i], "||", a))
			return (error_return("|"));
		if (ft_strnstr(&buff[i], ">>>", a))
			return (error_return(">>"));
		i += a;
		if (buff[i] && (34 == buff[i] || 39 == buff[i]))
			to_end_quote_length(buff[i], &buff[i], &i, &a);
	}
	return (NULL);
}

char	*parse_errors_again(char **line)
{
	int		i;
	char	*error;

	i = 0;
	while (line[i])
	{
		if (!ft_strncmp(line[i], "|", 2))
		{
			error = check_pipe_error(line, i);
			if (error)
				return (error);
		}
		if (is_redirect(line, i))
		{
			error = check_redir_error(line, i);
			if (error)
				return (error);
		}
		i++;
	}
	return (NULL);
}
