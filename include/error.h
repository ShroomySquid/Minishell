/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:29:50 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/04 11:27:13 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int 	error_dup(t_exec_st *exec_st);
int		error_malloc_HD(t_exec_st *exec_st, char **line_args, char *buff);
void	error_parsing(char *buff, char **line_args);


#endif
