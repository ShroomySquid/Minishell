/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:37:14 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/14 10:33:30 by fbarrett         ###   ########.fr       */
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

char	*check_ope_error(char *buff, int *i)
{
	int	a;

	a = 0;
	while (buff[*i + a] && 34 != buff[*i + a] && 39 != buff[*i + a])
		a++;
	if (buff[*i] && ft_strnstr(&buff[*i], "<<<", a))
		return ("<<");
	if (buff[*i] && ft_strnstr(&buff[*i], "||", a))
		return ("|");
	if (buff[*i] && ft_strnstr(&buff[*i], ">>>", a))
		return (">>");
	*i += a;
	if (buff[*i] && (34 == buff[*i] || 39 == buff[*i]))
		to_end_quote_length(buff[*i], buff, i, &a);
	return (NULL);
}

char	*parse_errors(char *buff)
{
	int		i;
	char	quote;
	char	*return_value;

	i = 0;
	if (!buff)
		return (NULL);
	quote = check_invalid_quote(buff);
	if (quote == '\'')
		return (error_return("\'"));
	if (quote == '"')
		return (error_return("\""));
	while (buff[i])
	{
		return_value = check_ope_error(buff, &i);
		if (return_value)
			return (error_return(return_value));
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
