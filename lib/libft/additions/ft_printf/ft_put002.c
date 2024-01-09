/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put002.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:36:34 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/02 15:42:53 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_putnbr(int n)
{
	int		ret;
	long	nbr;

	nbr = (long)n;
	ret = 0;
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		ret++;
		nbr = -nbr;
	}
	if (nbr > 9)
		ret += ft_putnbr(nbr / 10);
	ft_putchar_fd(nbr % 10 + '0', 1);
	return (ret + 1);
}

int	ft_putpointer(void *ptr)
{
	int	ret;

	ret = 0;
	ft_putstr_fd("0x", 1);
	ret += 2;
	ret += ft_putnbr_hex((unsigned long)ptr);
	return (ret);
}
