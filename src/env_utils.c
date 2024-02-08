/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:12:05 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/26 16:12:33 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*env_new(char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!new->value && !value)
		new->value = ft_strdup("");
	if (!new->name || !new->value)
	{
		free(new->name);
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}

void	env_delone(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	if (!env || !*env)
		return ;
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	env_clear(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}

t_env	*env_dup(t_env *env)
{
	t_env	*new_env;
	t_env	*tmp;

	new_env = NULL;
	while (env)
	{
		tmp = env_new(env->name, env->value);
		if (!tmp)
		{
			env_clear(&new_env);
			return (NULL);
		}
		env_add_back(&new_env, tmp);
		env = env->next;
	}
	return (new_env);
}
