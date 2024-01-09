/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:03:39 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:55:34 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Fonction qui enlève les whitespaces au début du string donné*/
static int	get_rid_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] < 14 && str[i] > 8))
		i++;
	return (i);
}

/* Fonction qui transforme un série de char en integer */
int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	final_nbr;

	if (!str)
		return (0);
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
	final_nbr *= neg;
	return (final_nbr);
}
