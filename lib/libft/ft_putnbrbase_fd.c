/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:12:17 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:35:20 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_verifiedbase_fd(unsigned int n, 
		int fd, char *base, unsigned int base_type)
{
	if (n > base_type)
	{
		ft_putnbr_verifiedbase_fd((n / base_type), fd, base, base_type);
		ft_putnbr_verifiedbase_fd((n % base_type), fd, base, base_type);
	}
	else
		write(fd, &base[n], 1);
}

void	ft_putnbr_base_fd(int n, int fd, char *base)
{
	unsigned int	temp_nbr;
	unsigned int	base_type;

	base_type = base_type_check(base);
	if (n < 0)
	{
		write(fd, "-", 1);
		temp_nbr = -1 * n;
	}
	else
		temp_nbr = n;
	if (temp_nbr > base_type && base_type > 1)
	{
		ft_putnbr_verifiedbase_fd((temp_nbr / base_type), fd, base, base_type);
		ft_putnbr_verifiedbase_fd((temp_nbr % base_type), fd, base, base_type);
	}
	else if (base_type > 1)
		write(fd, &base[temp_nbr], 1);
}
