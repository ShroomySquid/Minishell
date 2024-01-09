/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:14:44 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:04:28 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Crée un nouveau string à partir d'un string donné. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = ft_strlen(s);
	if (i - start < len)
		len = (i - start);
	if (i - start > i)
		len = 0;
	substring = malloc(len + 1);
	if (!substring || !s)
		return (NULL);
	if (i < start)
	{
		substring[0] = '\0';
		return (substring);
	}
	i = 0;
	while (i < (len) && s[start + i])
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
