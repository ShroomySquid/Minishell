/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:30 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/16 14:26:08 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Empty b_unset function
int	b_unset(char **args, char **env)
{
	(void)args;
	(void)env;
	return (0);
}

int	b_parent_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (env_find(env, args[i]))
			env_delone(&env, args[i]);
		else
		{
			ft_printf("minishell: unset: `%s': not a valid identifier\n",
				args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
