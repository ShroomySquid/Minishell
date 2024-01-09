/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:15:51 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/02 15:43:29 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	is_spec_printf(char *format, va_list ap)
{
	if (*format != '%')
		return (0);
	format++;
	if (!*format)
		return (-1);
	if (*format == 'c')
		return (ft_putchar((char)va_arg(ap, int)));
	else if (*format == 's')
		return (ft_putstr((char *)va_arg(ap, char *)));
	else if (*format == 'p')
		return (ft_putpointer((void *)va_arg(ap, void *)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr((int)va_arg(ap, int)));
	else if (*format == 'u')
		return (ft_putunbr((unsigned int)va_arg(ap, unsigned int)));
	else if (*format == 'x')
		return (ft_putnbr_hex((unsigned int)va_arg(ap, unsigned int)));
	else if (*format == 'X')
		return (ft_putnbr_hex_upper((unsigned int)va_arg(ap, unsigned int)));
	else if (*format == '%')
		return (ft_putchar('%'));
	return (-1);
}
