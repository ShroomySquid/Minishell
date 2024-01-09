/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:54:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 12:34:36 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui delete tous les éléments d'une liste chainé
 * et free la mémoire */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp_node = (**lst).next;
		ft_lstdelone(*lst, del);
		*lst = temp_node;
	}
	free(*lst);
	*lst = 0;
}
