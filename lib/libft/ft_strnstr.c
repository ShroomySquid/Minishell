/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:38:12 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 16:38:16 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui cherche si un string est présent à l'intérieur des len
 * premiers éléments du string. Retourne NULL si non trouvé, sinon retourne
 * l'adresse de la première occurence du substring dans le string. */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	a;
	size_t	b;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	if (!needle[0])
		return ((char *)&haystack[i]);
	while (haystack[i] && (i < len))
	{
		b = i;
		a = 0;
		while (haystack[b] == needle[a] && (b < len))
		{
			if (!needle[a + 1])
				return ((char *)&haystack[i]);
			a++;
			b++;
		}
		i++;
	}
	return (NULL);
}
