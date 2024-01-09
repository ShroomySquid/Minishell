/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:41:24 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/25 13:28:25 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui met une nouvelle node à la fin de la liste chainée */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!lst || !new)
		return ;
	last_node = ft_lstlast(*lst);
	if (!last_node)
	{
		*lst = new;
		return ;
	}
	last_node->next = new;
}
