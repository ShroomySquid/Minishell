/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:14:44 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 17:53:08 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	reset_len(unsigned int i, unsigned int start, size_t *len)
{
	if (i - start < *len)
		*len = (i - start);
	if (i - start > i)
		*len = 0;
	return (0);
}

/* Crée un nouveau string à partir d'un string donné. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	reset_len(i, start, &len);
	substring = malloc(len + 1);
	if (!substring)
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
