/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:20 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:57:35 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* renvoie la taille du str pour le malloc */
static int	check_size(long n)
{
	int	taille;

	taille = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		taille++;
	}
	while (n > 0)
	{
		taille++;
		n = n / 10;
	}
	return (taille);
}

/* prend le nbr transformer en positif et le transpose sur le nouveau str */
static void	int_sur_str(int nbr, int i, char *final_str)
{
	int	temp_nbr;
	int	divider;

	divider = 1;
	temp_nbr = nbr;
	while (temp_nbr > 9 || temp_nbr < -9)
	{
		temp_nbr = temp_nbr / 10;
		divider *= 10;
	}
	while (divider)
	{
		if (temp_nbr >= 0)
			final_str[i] = ((nbr / divider) + 48);
		else
			final_str[i] = (-1 *(nbr / divider) + 48);
		nbr -= (nbr / divider) * divider;
		divider = divider / 10;
		i++;
	}
	final_str[i] = '\0';
}

/* Fonction qui transforme un integer en son équivalent en string */
char	*ft_itoa(int n)
{
	char	*final_str;
	int		i;

	i = 0;
	final_str = malloc(check_size(n) + 1);
	if (!final_str)
		return (NULL);
	if (n < 0)
	{
		final_str[i] = '-';
		i++;
	}
	int_sur_str(n, i, final_str);
	return (final_str);
}
