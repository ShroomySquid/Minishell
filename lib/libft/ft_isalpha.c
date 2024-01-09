/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:18:06 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/24 10:06:53 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Fonction qui vérifie si le symbole est une lettre majuscule */
static int	is_upper(int letter)
{
	if (letter < 91 && letter > 64)
		return (1);
	return (0);
}

/* Fonction qui vérifie si le symbole est une lettre minuscule */
static int	is_lower(int letter)
{
	if (letter < 123 && letter > 96)
		return (1);
	return (0);
}

/* Fonction qui vérifie si le symbole est une lettre majuscule
 * ou minuscule */
int	ft_isalpha(int letter)
{
	if (is_upper(letter) || is_lower(letter))
		return (1);
	return (0);
}
