/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:50:36 by fbarrett          #+#    #+#             */
/*   Updated: 2023/11/05 18:16:43 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui imprime le integer donné sur le fd donné */
void	ft_putnbr_fd(int n, int fd)
{
	int	divider;
	int	temp_nbr;

	if (n < 0)
		write(fd, "-", 1);
	divider = 1;
	temp_nbr = n;
	while (temp_nbr > 9 || temp_nbr < -9)
	{
		temp_nbr = temp_nbr / 10;
		divider *= 10;
	}
	while (divider > 0)
	{
		if (n >= 0)
			temp_nbr = (n / divider) + 48;
		else
			temp_nbr = -1 * (n / divider) + 48;
		write(fd, &temp_nbr, 1);
		n -= ((n / divider) * divider);
		divider = divider / 10;
	}
}
