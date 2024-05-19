/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:05:51 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/12 14:08:19 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the command is a builtin, return true or false
static bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

// execute the builtin command
static void	execute_builtin(t_data *data, int i)
{
	char	*cmd;

	cmd = data->cmds[i]->cmd_array[0];
	data->builtin_count++;
	if (set_redirections(data, i) == ERROR)
		return ;
	if (ft_strcmp(cmd, "echo") == 0)
		ms_echo(data, i);
	else if (ft_strcmp(cmd, "cd") == 0)
		ms_cd(data, i);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ms_pwd(data, i);
	else if (ft_strcmp(cmd, "export") == 0)
		ms_export(data, i);
	else if (ft_strcmp(cmd, "unset") == 0)
		ms_unset(data, i);
	else if (ft_strcmp(cmd, "env") == 0)
		ms_env(data, i);
	else if (ft_strcmp(cmd, "exit") == 0)
		ms_exit(data, i);
	if (reset_stdin_out(data) == ERROR)
		err_msg("reset_stdin_out failed");
}

// execute a single command
int	execute_command(t_data *data, int i)
{
	pid_t	pid;

	if (data->cmds[i]->no_infile || data->cmds[i]->no_outfile)
		data->exit_status = 1;
	else if (is_builtin(data->cmds[i]->cmd_array[0]))
		execute_builtin(data, i);
	else
	{
		data->exit_status = 0;
		pid = fork();
		if (pid == -1)
			return (err_msg(strerror(errno)), ERROR);
		if (pid == 0)
			child_process(data, i);
		add_pid(data, pid);
	}
	return (OK);
}
