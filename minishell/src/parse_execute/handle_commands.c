/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:10:46 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 10:30:20 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle one command
// example: "grep a > output.txt"
// return ERROR if any of the steps fail, otherwise return OK
static int	handle_command(t_data *data, int i)
{
	if (set_cmd_in_out(data, i) == ERROR)
		return (err_msg("set_cmd_in_out failed"), ERROR);
	if (set_cmd_data(data, i) == ERROR)
		return (err_msg("set_cmd_data failed"), ERROR);

	// ft_printf_fd(2, "| cmd: %s\n", data->cmds[i]->cmd_array[0]); // for testing
	// ft_printf_fd(2, "| path: %s\n", data->cmds[i]->cmd_path); // for testing
	// ft_printf_fd(2, "| fd_in: %d\n", data->cmds[i]->fd_in); // for testing
	// ft_printf_fd(2, "|_fd_out: %d\n", data->cmds[i]->fd_out); // for testing

	if (execute_command(data, i) == ERROR)
		return (ERROR);
	return (OK);
}

// handle commands between pipes
// example: "ls -l | sort | grep a > output.txt"
// return ERROR if any of the steps fail, otherwise return OK
int	handle_commands(t_data *data)
{
	int	i;

	i = 0;
	while (data->line_split[i])
	{
		if (handle_command(data, i) == ERROR)
			return (ERROR);
		i++;
	}
	close_pipes(data);
	wait_for_processes(data);
	return (OK);
}
