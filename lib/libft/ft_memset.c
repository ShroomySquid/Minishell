/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:54:54 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:59:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* écrit la valeur donné dans le array donné pour la taille donné. */
void	*ft_memset(void *b, int c, size_t len)
{
	char	*char_b;

	if (!b)
		return (NULL);
	char_b = b;
	while (len)
	{
		len--;
		char_b[len] = (unsigned char)c;
	}
	return (b);
}
