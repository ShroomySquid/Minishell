/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:36:54 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:02:13 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copie un string sur un autre string pour une taille donnée
 * Retourne la taille de src */
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		return_value;

	if (!dest || !src)
		return (0);
	i = 0;
	return_value = 0;
	while (src[i] && dstsize > i + 1)
	{
		dest[i] = src[i];
		i++;
		return_value++;
	}
	if (dstsize > 0)
		dest[i] = '\0';
	while (src[return_value])
		return_value++;
	return (return_value);
}
