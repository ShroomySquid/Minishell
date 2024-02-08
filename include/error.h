/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:29:50 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/06 10:09:54 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int		error_dup(t_exec_st *exec_st);
int		error_malloc_hd(t_exec_st *exec_st, char **line_args);
void	error_parsing(char **line_args);

#endif
