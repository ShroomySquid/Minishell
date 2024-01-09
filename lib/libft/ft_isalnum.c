/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:44:22 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/25 14:59:28 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui vérifie si le symbole est une lettre ou un chiffre */
int	ft_isalnum(int num)
{
	if (ft_isdigit(num) || ft_isalpha(num))
		return (1);
	return (0);
}
