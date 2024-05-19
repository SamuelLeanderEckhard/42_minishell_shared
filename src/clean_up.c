/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:36 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/24 22:18:38 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// close the file descriptors in the pipes array
void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		if (data->pipes[i][0] != -1)
		{
			close(data->pipes[i][0]);
			data->pipes[i][0] = -1;
		}
		if (data->pipes[i][1] != -1)
		{
			close(data->pipes[i][1]);
			data->pipes[i][1] = -1;
		}
		i++;
	}
}

// free all allocated memory in the pipes array and close the file descriptors
void	free_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		free(data->pipes[i]);
		data->pipes[i] = NULL;
		i++;
	}
	free(data->pipes);
	data->pipes = NULL;
}

// free allocated memory in the command structure and close file descriptors
static void	clean_up_cmd(t_cmd *cmd)
{
	if (cmd->cmd_array)
	{
		ft_free_str_arr(cmd->cmd_array);
		cmd->cmd_array = NULL;
	}
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	if (cmd->fd_in != -1)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out != -1)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	free(cmd);
}

// free all allocated memory in the cmds array and close file descriptors
void	clean_up_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		clean_up_cmd(cmds[i++]);
	free(cmds);
}

// free all allocated memory and close the file descriptors
void	clean_up(t_data *data)
{
	if (data)
	{
		if (data->env)
			ft_free_str_arr(data->env);
		if (data->line)
			free(data->line);
		if (data->line_split)
			ft_free_str_arr(data->line_split);
		if (data->command_split)
			ft_free_str_arr_2d(data->command_split);
		if (data->cmd_paths)
			ft_free_str_arr(data->cmd_paths);
		if (data->cmds)
			clean_up_cmds(data->cmds);
		if (data->pipes)
			free_pipes(data);
		free(data->pids);
		close(data->fd_stdin);
		close(data->fd_stdout);
	}
}
