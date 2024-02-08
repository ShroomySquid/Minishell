/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:13:53 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/04 11:32:48 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "define.h"
# include "minishell.h"

t_env			*env_innit(char **env);
void			env_add_back(t_env **alst, t_env *new);
t_env			*env_new(char *name, char *value);
void			env_clear(t_env **lst);
t_env			*env_dup(t_env *env);
char			**env_to_tab(t_env *env);
t_env			*env_find(t_env *env, char *name);
void			env_delone(t_env **env, char *name);

#endif
