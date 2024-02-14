/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:04:47 by fbarrett          #+#    #+#             */
/*   Updated: 2023/10/25 13:29:34 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fonction qui applique la fonction f sur chaque contenu de chaque node
 * de la liste chainé */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp_node;

	if (!lst || !f)
		return ;
	temp_node = lst;
	while (temp_node)
	{
		f(temp_node->content);
		temp_node = temp_node->next;
	}
}
