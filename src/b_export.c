/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:06 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/16 14:26:13 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_char_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		j = i;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	b_export_no_args(t_env *env)
{
	char	**tab;
	char	**hold;

	tab = env_to_tab(env);
	hold = tab;
	if (!tab)
		return (1);
	sort_char_tab(tab);
	while (*tab)
	{
		ft_printf("declare -x %s\n", *tab);
		free(*tab);
		tab++;
	}
	free(hold);
	return (0);
}

int	b_export(char **args, char **envp)
{
	if (!args[1])
	{
		sort_char_tab(envp);
		while (*envp)
		{
			ft_printf("declare -x %s\n", *envp);
			envp++;
		}
	}
	return (0);
}

int	b_parent_export(char **args, t_env *env)
{
	int		i;
	char	**split;

	i = 0;
	if (!args[1])
		return (b_export_no_args(env));
	split = NULL;
	while (args[++i])
	{
		free_all(split);
		split = ft_split(args[i], '=');
		if (!split || !split[0] || (!split[1] && !ft_strchr(args[i], '=')))
			continue ;
		if (!split[1])
			split[1] = ft_strdup("");
		if (env_find(env, split[0]))
			env_find(env, split[0])->value = ft_strdup(split[1]);
		else
			env_add_back(&env, env_new(split[0], split[1]));
	}
	return (0);
}