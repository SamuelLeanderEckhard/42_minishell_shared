/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:05:51 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/24 11:10:23 by bszabo           ###   ########.fr       */
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

// child process, execute the command if possible, otherwise exit
static void	child_process(t_data *data, int i)
{
	t_cmd	*cmd;

	cmd = data->cmds[i];
	if (set_redirections(data, i) == ERROR)
		close_pipes(data), clean_up(data), exit(1);
	close_pipes(data);
	if (cmd->cmd_array[0][0] == '\0')
		clean_up(data), exit(0);
	if (cmd->cmd_path == NULL)
	{
		err_msg2(cmd->cmd_array[0], "command not found");
		clean_up(data), exit(127);
	}
	sig_cases(CHILD);
	execve(cmd->cmd_path, cmd->cmd_array, data->env);
	err_msg(strerror(errno)), clean_up(data), exit(1);
}

// execute a single command
int	execute_command(t_data *data, int i)
{
	pid_t	pid;
	// ft_printf_fd(2, "-------- execute_command --------\n"); // for testing
	// ft_printf_fd(2, "%s fd_in: %d | fd_out: %d\n", data->cmds[i]->cmd_array[0], data->cmds[i]->fd_in, data->cmds[i]->fd_out); // for testing

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
