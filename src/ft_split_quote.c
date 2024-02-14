/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:02:04 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 17:53:06 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_quote(char *s, char quote)
{
	s++;
	while (*s && *s != quote)
		s++;
	if (*s)
		s++;
	if (*s == 39 || *s == 34)
		return (skip_quote(s, *s));
	return (s);
}

/* Fonction qui compte le nombre de string qui seront créé */
int	count_str_quote(char *s)
{
	int	str_nbr;

	str_nbr = 0;
	while (*s)
	{
		while (is_white_space(*s))
			s++;
		if (*s)
			str_nbr++;
		if (*s == 39)
			s = skip_quote(s, 39);
		else if (*s == 34)
			s = skip_quote(s, 34);
		while (*s && !is_white_space(*s))
			s++;
	}
	return (str_nbr);
}

char	*find_next_str(char *s)
{
	char	quote;

	while (*s && !is_white_space(*s))
	{
		if (39 == *s || 34 == *s)
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			if (*s == quote)
				s++;
		}
		else
			s++;
	}
	return (s);
}

static char	**split_it_quote(char *s, char **final_array)
{
	char	*end_str;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && is_white_space(*s))
			s++;
		if (*s)
		{
			end_str = find_next_str(s);
			final_array[i] = ft_substr(s, 0, (end_str - s));
			i++;
			if (!final_array[i - 1])
				return (free_all(final_array));
			s = end_str;
		}
	}
	final_array[i] = 0;
	return (final_array);
}

/* Fonction qui sépare un string en une série de sous-string */
char	**ft_split_quote(char const *s)
{
	char	**final_array;

	if (!s)
		return (0);
	final_array = (char **)malloc(
			(count_str_quote((char *)s) + 1) * sizeof(unsigned long int));
	if (!final_array)
		return (0);
	return (split_it_quote((char *) s, final_array));
}
