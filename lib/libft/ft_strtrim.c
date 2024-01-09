/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:29:40 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:04:16 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Test si le charactère donné fait partie du set */
static int	test_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/* Crée le string final à partir du point i dans s1 jusqu'au point a */
static char	*final_str(char const *s1, int a, int i)
{
	char	*new_str;
	int		b;

	b = 0;
	if (!s1[i])
	{
		new_str = malloc(1);
		if (!new_str)
			return (0);
	}
	else
	{
		new_str = malloc(a - i + 2);
		if (!new_str)
			return (NULL);
		while ((i + b) <= a)
		{
			new_str[b] = s1[i + b];
			b++;
		}
	}
	new_str[b] = '\0';
	return (new_str);
}

/* Enlève les charactères du set du début et de la fin du str */
char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	a;

	if (!s1 || !set)
		return (NULL);
	if (!s1[0])
		return (ft_strdup(""));
	i = 0;
	a = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (!test_set(s1[i], set))
			break ;
		i++;
	}
	while (s1[a])
	{
		if (!test_set(s1[a], set))
			break ;
		a--;
	}
	return (final_str(s1, a, i));
}
