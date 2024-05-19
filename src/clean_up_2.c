/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 07:41:24 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/08 13:16:02 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// close file descriptor if it is not -1 or one of the standard file descriptors
// and set it to -1
void	reset_fd(int fd)
{
	if (fd != -1 && fd != STDIN_FILENO && fd != STDOUT_FILENO
		&& fd != STDERR_FILENO)
	{
		close(fd);
		fd = -1;
	}
}

// reset stdin and stdout file descriptors to their original values
int	reset_stdin_out(t_data *data)
{
	if (dup2(data->fd_stdin, STDIN_FILENO) == -1
		|| dup2(data->fd_stdout, STDOUT_FILENO) == -1)
		return (ERROR);
	return (OK);
}

// first part of the clean_up_loop function
static void	clean_up_loop_1(t_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->line_split)
	{
		ft_free_str_arr(data->line_split);
		data->line_split = NULL;
	}
	if (data->command_split)
	{
		ft_free_str_arr_2d(data->command_split);
		data->command_split = NULL;
	}
	if (data->cmd_paths)
	{
		ft_free_str_arr(data->cmd_paths);
		data->cmd_paths = NULL;
	}
	if (data->cmds)
	{
		clean_up_cmds(data->cmds);
		data->cmds = NULL;
	}
}

// free allocated memory in the main loop and close the file descriptors
void	clean_up_loop(t_data *data)
{
	clean_up_loop_1(data);
	if (data->pipes)
	{
		close_pipes(data);
		free_pipes(data);
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (reset_stdin_out(data) == ERROR)
		err_msg("reset_stdin_out failed");
}
