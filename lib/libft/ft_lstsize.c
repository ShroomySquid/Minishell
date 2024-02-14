/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:28:02 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/25 13:20:19 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui retourne le nombre de node dans la liste chainée */
int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp_list;

	if (!lst)
		return (0);
	i = 0;
	temp_list = lst;
	while (temp_list)
	{
		i++;
		temp_list = temp_list->next;
	}
	return (i);
}
