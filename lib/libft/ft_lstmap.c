/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:09:55 by fbarrett          #+#    #+#             */
/*   Updated: 2023/11/08 13:33:02 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui renvoie une nouvelle liste chainé avec le même node que la
 * liste chainée passé mais avec la fonction f appliqué sur chaque élément.
 * Si malloc fail, on utilise del sur les éléments précédents */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;
	t_list	*temp_node;

	if (!lst || !f || !del)
		return (0);
	new_list = 0;
	temp_node = lst;
	while (temp_node)
	{
		new_node = ft_lstnew(temp_node->content);
		if (!new_node)
		{
			del(new_node);
			ft_lstclear(&new_node, del);
			return (0);
		}
		new_node->content = f(new_node->content);
		ft_lstadd_back(&new_list, new_node);
		temp_node = temp_node->next;
	}
	return (new_list);
}
