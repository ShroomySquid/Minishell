/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:10:51 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:03:35 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Comme strchr, mais on retourne le dernier trouvé plutôt que le premier */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	if ((char) c == '\0')
		return ((char *)&s[i]);
	i--;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
