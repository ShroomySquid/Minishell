/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:11:01 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:58:33 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Renvoie la première occurence d'un charactère (donnée en int) dans un 
 * array donné. retourne zero si aucun charactère correspondant trouvé */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*char_s;

	if (!s)
		return (NULL);
	i = 0;
	char_s = (unsigned char *)s;
	while (i < n)
	{
		if (char_s[i] == (unsigned char) c)
			return ((void *)&char_s[i]);
		i++;
	}
	return (0);
}
