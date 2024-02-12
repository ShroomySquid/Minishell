/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:54:43 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/12 13:41:50 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Écrit des zéros partout dans le array donné pour la taille donné */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
