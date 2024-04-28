/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:42:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/23 12:50:47 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main loop for minishell
// handle signals, read line, add it to history, parse, execute, and free line
// return ERROR if any of the steps fail
static int	main_loop(t_data *data)
{
	while (1)
	{
		clean_up_loop(data);
		sig_cases(INTERACTIVE);
		data->line = readline(PROMPT);
		sig_cases(NON_INTERACTIVE);
		if (g_signal == CTRL_C && g_signal--)
			data->exit_status = 130;
		if (!data->line)
			return (printf("exit\n"), ERROR);
		if (ft_strlen(data->line) > 0)
		{
			add_history(data->line);
			if (check_line(data) == ERROR)
				continue;
			if (parse_execute_line(data) == ERROR)
				continue;
		}
	}
	return (OK);
}

// 1. check arguments
// 2. initialize data
// 3. main loop
int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	if (argc != 1 || argv[1] || !env)
		return (ft_printf_fd(2, ARGS_ERROR), ERROR);
	if (init(&data, env) == ERROR)
		return (clean_up(&data), ERROR);
	if (main_loop(&data) == ERROR)
		return (clean_up(&data), data.exit_status);
}
