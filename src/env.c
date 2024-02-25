/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:24:32 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/25 08:37:43 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_len(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env->next;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_env	*env_innit(char **envp)
{
	t_env	*env;
	char	**split;
	int		i;

	i = -1;
	if (!envp)
		return (NULL);
	env = env_new(NULL, NULL);
	while (envp[++i])
	{
		split = ft_calloc(3, sizeof(char *));
		if (!split)
			return (NULL);
		split[1] = ft_strdup(ft_strchr(envp[i], '=') + 1);
		split[0] = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		if (!split[0] || (!split[1] && ft_strchr(envp[i], '=')[1]))
		{
			env_clear(&env);
			free_all(split);
			return (NULL);
		}
		env_add_back(&env, env_new(split[0], split[1]));
		free_all(split);
	}
	return (env);
}

char	**env_to_tab(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;
	char	*name;

	i = 0;
	tmp = env->next;
	envp = ft_calloc(env_len(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (tmp)
	{
		if (!tmp->value)
		{
			tmp = tmp->next;
			continue ;
		}
		name = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(name, tmp->value);
		free(name);
		if (!envp[i++])
			return (free_all(envp), NULL);
		tmp = tmp->next;
	}
	return (envp);
}

t_env	*export_find(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*env_find(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name) && tmp->value)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
