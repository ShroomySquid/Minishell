/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:29:50 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 17:15:19 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int		error_dup(t_exec_st *exec_st);
int		error_malloc_hd(t_exec_st *exec_st, char **line_args);
void	error_parsing(char *error);
void	error_cmd_not_found(t_exec_st *exec_st, int *return_value);
void	error_no_file(t_exec_st *exec_st, int *return_value, char **cmd_paths);
void	error_is_dir(t_exec_st *exec_st, int *return_value);
void	error_permission_d(t_exec_st *exec_st,
			int *return_value, char **cmd_paths);
int		failed_cmd_msg(t_exec_st *exec_st, char **cmd_paths);
char	*parse_errors(char *buff);
char	*parse_errors_again(char **line);
char	*error_return(char *token);
char	check_invalid_quote(char *buff);

#endif
