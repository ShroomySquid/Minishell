/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:17:44 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/09 14:14:47 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include "libft/libft.h"

char	*seek_cmd(char *cmd, char **envp);
char	**ft_split_quote(char const *s, char c);
#endif
