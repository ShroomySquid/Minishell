/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:30:18 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:55:22 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_rid_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] < 14 && str[i] > 8))
		i++;
	return (i);
}

float	ft_atof_decimals(const char *str, int max_dec, int i, float final_nbr)
{
	int		div;
	float	temp_nbr;

	div = 10;
	if (str[i] == ',' | str[i] == '.')
		i++;
	while (str[i] < 58 && str[i] > 47 && max_dec > 0)
	{
		temp_nbr = str[i] - 48;
		temp_nbr = temp_nbr / div;
		final_nbr += temp_nbr;
		div *= 10;
		i++;
		max_dec--;
	}
	return (final_nbr);
}

float	ft_atof(const char *str, int max_dec)
{
	int		i;
	float	neg;
	float	final_nbr;

	if (!str)
		return (NULL);
	i = get_rid_whitespaces((char *)str);
	neg = 1;
	final_nbr = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] < 58 && str[i] > 47)
	{
		final_nbr *= 10;
		final_nbr += (str[i] - 48);
		i++;
	}
	final_nbr = ft_atof_decimals(str, max_dec, i, final_nbr) * neg;
	return (final_nbr);
}
