/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:26:52 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:55:51 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Alloue count fois size de mémoire et set la mémoire alloué à zero */
void	*ft_calloc(size_t count, size_t size)
{
	void	*new_pointer;

	new_pointer = malloc(count * size);
	if (!new_pointer)
		return (NULL);
	ft_bzero(new_pointer, count * size);
	return (new_pointer);
}
