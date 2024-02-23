/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:55 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/23 17:30:08 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"

int	b_exit_mock(char **args, char **env)
{
	(void)env;
	if (!args)
		return (0);
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (args[1] && !ft_isdigit(*(args[1]))
		&& args[1][0] != '-' && args[1][0] != '+')
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (args[1])
		return (ft_atoi(args[1]));
	return (0);
}

int	b_exit(char **args, int custom_exit)
{
	int	exit_code;

	if (!custom_exit)
		exit_code = EXIT_SUCCESS;
	else
		exit_code = custom_exit;
	if (!args)
		exit(exit_code);
	else if (args[1] && !ft_isdigit(*(args[1]))
		&& args[1][0] != '-' && args[1][0] != '+')
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 255;
	}
	else if (args[1])
		exit_code = ft_atoi(args[1]);
	free_all(args);
	exit(exit_code);
}

int	b_true_exit(char **buff, void *exec_st_t, t_env *env, bool verbose)
{
	t_exec_st	*exec_st;
	int			ret;

	(void) verbose;
	exec_st = (t_exec_st *)exec_st_t;
	ret = exec_st->ret;
	if (buff && buff[1] && buff[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exec_st->ret = 1;
		return (1);
	}
	if (exec_st->hd_list)
		free(exec_st->hd_list);
	if (exec_st->ope_quotes)
		free_all(exec_st->ope_quotes);
	close(exec_st->temp_stdin);
	close(exec_st->temp_stdout);
	free(exec_st);
	env_clear(&env);
	b_exit(buff, ret);
	return (0);
}
