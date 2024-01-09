/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:30:31 by fbarrett          #+#    #+#             */
/*   Updated: 2023/11/09 09:05:30 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Comme memcpy mais évite de transformer la source dans certains cas
 * spécifiques */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*char_dst;
	char	*not_const_src;
	size_t	i;

	if (!dst || !src)
		return (dst);
	char_dst = dst;
	not_const_src = (char *) src;
	i = 0;
	if (src < dst)
	{
		while (len)
		{
			len--;
			char_dst[len] = not_const_src[len];
		}
	}
	i = -1;
	while (++i < len)
		char_dst[i] = not_const_src[i];
	return (dst);
}
