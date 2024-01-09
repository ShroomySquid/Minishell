/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:54:56 by gcrepin           #+#    #+#             */
/*   Updated: 2023/10/31 12:30:47 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_vprintf(const char *format, va_list ap)
{
	int	index;
	int	error;
	int	ret;

	ret = 0;
	error = 0;
	index = 0;
	while (format[index])
	{
		error = is_spec_printf((char *)&format[index], ap);
		if (error == -1)
			return (-1);
		if (error)
		{
			ret += error * (error != -2);
			index += 2;
		}
		else
			ft_putchar_fd(format[index++], 1);
		ret += error == 0;
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}
