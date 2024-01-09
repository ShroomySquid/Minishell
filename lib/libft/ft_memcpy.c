/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:03:24 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/24 13:25:30 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copie un array donné dans la destination donné pour la taille donnée */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*char_dst;
	char	*char_src;
	size_t	i;

	if (!dst || !src)
		return (dst);
	i = 0;
	char_dst = (char *)dst;
	char_src = (char *)src;
	while (i < n)
	{
		char_dst[i] = char_src[i];
		i++;
	}
	return (dst);
}
