/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:10:08 by fbarrett          #+#    #+#             */
/*   Updated: 2023/11/09 09:10:22 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Identifie la taille de la base, renvoie 0 dans le cas d'une base invalide */
int	base_type_check(char *base)
{
	int	a;
	int	i;

	i = 0;
	while (base[i])
	{
		a = 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (base[i + a])
		{
			if (base[i] == base[i + a])
				return (0);
			a++;
		}
		i++;
	}
	return (i);
}
