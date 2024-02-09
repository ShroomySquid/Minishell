/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:56:38 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/09 16:56:44 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	b_identifier_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	b_export_final(t_env *env, char *arg)
{
	char	**split;

	split = ft_split(arg, '=');
	if (!split || !split[0] || (!split[1] && !ft_strchr(arg, '=')))
	{
		free_all(split);
		return ;
	}
	if (!split[1])
		split[1] = ft_strdup("");
	if (env_find(env, split[0]))
		env_find(env, split[0])->value = ft_strdup(split[1]);
	else
		env_add_back(&env, env_new(split[0], split[1]));
	free_all(split);
}
