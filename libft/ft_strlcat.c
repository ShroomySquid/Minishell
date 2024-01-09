/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:27 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:01:58 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Rajoute un string après le string de la dest. retourne la taille de dest
 * + src sauf dans le cas ou dest est plus grand que dstsize */
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	a;
	size_t	return_value;

	i = 0;
	a = 0;
	if (!dest || !src)
		return (0);
	while (dest[i])
		i++;
	while (src[a])
		a++;
	if (i > dstsize)
		return (dstsize + a);
	return_value = i + a;
	a = 0;
	while (src[a] && (i + 1) < dstsize)
	{
		dest[i] = src[a];
		i++;
		a++;
	}
	dest[i] = '\0';
	return (return_value);
}
