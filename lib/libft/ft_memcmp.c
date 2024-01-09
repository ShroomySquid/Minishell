/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:25:18 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:58:46 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compare deux array, retourne 0 si identique. Retourne valeur positive si
 * la première valeure différente est plus grande dans le premier array,
 * sinon retourne une valeur négative. */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*char_s1;
	unsigned char	*char_s2;

	if (!s1 || !s2)
		return (0);
	i = 0;
	char_s1 = (unsigned char *)s1;
	char_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (char_s1[i] != char_s2[i])
			return (char_s1[i] - char_s2[i]);
		i++;
	}
	return (0);
}
