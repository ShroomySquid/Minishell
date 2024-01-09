/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:37:14 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/24 10:07:22 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Fonction qui vérifie si le symbole est un chiffre */
int	ft_isdigit(int digit)
{
	if (digit < 58 && digit > 47)
		return (1);
	return (0);
}
