/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:02:16 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/24 10:09:37 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Fonction qui vérifie si le symbole est affichable */
int	ft_isprint(int printable)
{
	if (printable > 31 && printable < 127)
		return (1);
	return (0);
}
