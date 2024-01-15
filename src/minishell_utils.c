/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:06:19 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/15 12:13:11 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_array(char **array_str)
{
        int i;

        i = 0;
        while (array_str[i])
        {
                ft_printf("%s\n", array_str[i]);
                i++;
        }
}

char    **ft_sub_array(char **array, int start, int end)
{
        char    **sub_array;
        int i;

        i = 0;
        if (start >= end)
                return (NULL);
        sub_array = ft_calloc(end - start + 1, sizeof(char*));
        while (array[start + i] && (start + i) <= end)
        {
                sub_array[i] = ft_strdup(array[start + i]);
                i++;
        }
        sub_array[i] = 0;
        return (sub_array);
}
