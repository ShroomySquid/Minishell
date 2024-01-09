/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:13:00 by fbarrett          #+#    #+#             */
/*   Updated: 2023/12/01 11:56:40 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sorted(long *list, int len)
{
	int	i;

	i = 1;
	while (list[i] && (list[i - 1] <= list[i]))
		i++;
	if (i < len)
		return (0);
	return (1);
}

int	is_rev_sorted(long *list, int len)
{
	int	i;

	i = 1;
	while (list[i] && list[i - 1] >= list[i])
		i++;
	if (i < len)
		return (0);
	return (1);
}

int	find_biggest(long *list, int len)
{
	int	biggest;
	int	i;

	biggest = list[0];
	i = 1;
	while (i < len)
	{
		if (list[i] > biggest)
			biggest = list[i];
		i++;
	}
	return (biggest);
}

int	find_smallest(long *list, int len)
{
	int	smallest;
	int	i;

	smallest = list[0];
	i = 1;
	while (i < len)
	{
		if (list[i] < smallest)
			smallest = list[i];
		i++;
	}
	return (smallest);
}
