/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:55:30 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/02 15:43:04 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

int	ft_printf(const char *str, ...);
int	ft_putunbr(unsigned int n);
int	ft_putstr(char *str);
int	ft_putnbr_hex(unsigned long n);
int	ft_putnbr_hex_upper(unsigned long n);
int	ft_putchar(char c);
int	ft_putnbr(int n);
int	ft_putpointer(void *ptr);

#endif
