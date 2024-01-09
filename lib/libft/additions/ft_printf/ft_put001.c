/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put001.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:10:43 by gcrepin           #+#    #+#             */
/*   Updated: 2023/10/20 13:12:02 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putunbr(unsigned int n)
{
	int	ret;

	ret = 0;
	if (n > 9)
		ret += ft_putunbr(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
	return (ret + 1);
}

int	ft_putstr(char *str)
{
	if (str)
	{
		if (!*str)
			return (-2);
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	ft_putstr_fd("(null)", 1);
	return (6);
}

int	ft_putnbr_hex(unsigned long n)
{
	int	ret;

	ret = 0;
	if (n > 15)
		ret += ft_putnbr_hex(n / 16);
	if (n % 16 < 10)
		ft_putchar_fd(n % 16 + '0', 1);
	else
		ft_putchar_fd(n % 16 - 10 + 'a', 1);
	return (ret + 1);
}

int	ft_putnbr_hex_upper(unsigned long n)
{
	int	ret;

	ret = 0;
	if (n > 15)
		ret += ft_putnbr_hex_upper(n / 16);
	if (n % 16 < 10)
		ft_putchar_fd(n % 16 + '0', 1);
	else
		ft_putchar_fd(n % 16 - 10 + 'A', 1);
	return (ret + 1);
}
