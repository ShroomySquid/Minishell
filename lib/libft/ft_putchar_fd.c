/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:55:45 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/25 13:26:39 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Écrit le charactère donné dans le fd donné */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
