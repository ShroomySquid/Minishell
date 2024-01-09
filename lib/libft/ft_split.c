/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:39:18 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:00:41 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui compte le nombre de string qui seront créé */
static int	count_str(char *s, char c)
{
	size_t	str_nbr;

	str_nbr = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			str_nbr++;
		while (*s != c && *s)
			s++;
	}
	return (str_nbr);
}

/* Fonction qui free la mémoire de Final_array 
 * et des strings enregistrés sur lui */
char	**free_all(char **final_array)
{
	int	i;

	i = 0;
	while (final_array[i])
	{
		free(final_array[i]);
		i++;
	}
	free(final_array);
	return (0);
}

static char	**split_it(char *s, char c, char **final_array)
{
	int		i;
	char	*end_str;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			end_str = ft_strchr(s, c);
			if (end_str)
				final_array[i++] = ft_substr(s, 0, (end_str - s));
			else
				final_array[i++] = ft_substr(s, 0, ft_strlen(s));
			if (!final_array[i - 1])
				return (free_all(final_array));
			while (*s != c && *s)
				s++;
		}
	}
	final_array[i] = 0;
	return (final_array);
}

/* Fonction qui sépare un string en une 
 * série de sous-string à chaque caractère c */
char	**ft_split(char const *s, char c)
{
	char	**final_array;

	final_array = (char **)malloc(
			(count_str((char *)s, c) + 1) * sizeof(char *));
	if (!s || !final_array)
		return (NULL);
	return (split_it((char *)s, c, final_array));
}
