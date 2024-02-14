/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:10:51 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/01 10:15:43 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Cherche un charactère dans une chaine de charactère. Retourne l'adresse
 * du premier charactère correspondant trouvé */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)(s + i));
	return (0);
}
