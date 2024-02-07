/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:55 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/26 10:51:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"


int	b_exit_mock(char **args, char **env)
{
	(void)env;
	if (!args)
		return(0);
	if (args[1] && args[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (args[1] && !ft_isdigit(*(args[1])))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n",
			args[1]);
		return (255);
	}
	else if (args[1])
		return (ft_atoi(args[1]));
	return(0);
}

int	b_exit(char **args, char **env)
{
	int	exit_code;

	(void)env;
	exit_code = EXIT_SUCCESS;
	if (!args)
		exit(0);
	if (args[1] && args[2])
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else if (args[1] && !ft_isdigit(*(args[1])))
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			args[1]);
		exit_code = 255;
	}
	else if (args[1])
		exit_code = ft_atoi(args[1]);
	if (!env)
		free_all(args);
	exit(exit_code);
}

int b_true_exit(char **buff, void *exec_st_t, t_env *env, bool verbose)
{
	t_exec_st *exec_st;

	ft_printf("PID: %d\n", getpid());
	exec_st = (t_exec_st *)exec_st_t;
	if (buff && buff[1] && buff[2])
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	if (exec_st->HD_list)
		free(exec_st->HD_list);
	if (exec_st->ope_quotes)
		free_all(exec_st->ope_quotes);
	free(exec_st);
	env_clear(&env);
	if (verbose)
	{
		rl_replace_line("", 0);
	rl_on_new_line();
	rl_clear_history();
	ft_printf("\n[exit]\n");
	}
	b_exit(buff, NULL);
	return (0);
}
