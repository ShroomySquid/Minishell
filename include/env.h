/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:13:53 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/26 16:14:00 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENV_H
# define ENV_H

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

# include "minishell.h"

t_env			*env_innit(char **env);
void			env_add_back(t_env **alst, t_env *new);
void			env_add_front(t_env **alst, t_env *new);
t_env			*env_new(char *name, char *value);
void			env_clear(t_env **lst);
t_env			*env_dup(t_env *env);
char			**env_to_tab(t_env *env);
t_env			*env_find(t_env *env, char *name);

#endif
