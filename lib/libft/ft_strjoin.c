/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:49:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:01:39 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Concatenate le s1 et le s2 dans le final_str */
static char	*ft_conc_str(char *final_str, char const *s1, char const *s2)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (s1[i])
	{
		final_str[i] = s1[i];
		i++;
	}
	while (s2[a])
	{
		final_str[i + a] = s2[a];
		a++;
	}
	final_str[i + a] = '\0';
	return (final_str);
}

/* Crée un nouveau string qui est le s1 suivis du s2 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;

	if (!s1 || !s2)
		return (NULL);
	final_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!final_str)
		return (NULL);
	return (ft_conc_str(final_str, s1, s2));
}
