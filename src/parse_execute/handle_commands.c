/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:10:46 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/12 10:28:41 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// remove quotes around the strings in command_split and in cmd_array
static void	remove_quotes_around(t_data *data, int i)
{
	int		j;
	char	*temp;

	temp = NULL;
	j = 0;
	if (ft_strcmp(data->cmds[i]->cmd_array[0], "echo") == 0
		|| ft_strcmp(data->cmds[i]->cmd_array[0], "unset") == 0)
		return ;
	while (data->command_split[i][j])
	{
		temp = data->command_split[i][j];
		data->command_split[i][j] = remove_quotes(temp);
		j++;
	}
	j = 0;
	while (data->cmds[i]->cmd_array[j])
	{
		temp = data->cmds[i]->cmd_array[j];
		data->cmds[i]->cmd_array[j] = remove_quotes(temp);
		j++;
	}
}

// handle one command
// example: "grep a > output.txt"
// return ERROR if any of the steps fail, otherwise return OK
static int	handle_command(t_data *data, int i)
{
	if (set_cmd_in_out(data, i) == ERROR)
	{
		data->exit_status = 2;
		return (ERROR);
	}
	if (set_cmd_data(data, i) == ERROR)
		return (err_msg("set_cmd_data failed"), ERROR);
	remove_quotes_around(data, i);
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
