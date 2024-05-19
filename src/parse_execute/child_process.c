/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:17:49 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/10 12:06:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle the case when 'cmd_name' is not a valid, executable command,
// but it is a file
// print an error message and return the appropriate exit code
static int	handle_no_cmd_file(char *cmd_name)
{
	if (access(cmd_name, X_OK) != 0 && errno == EACCES
		&& ft_strchr(cmd_name, '/'))
		return (err_msg2(cmd_name, "Permission denied"), 126);
	else if (ft_strchr(cmd_name, '/'))
		return (err_msg2(cmd_name, "No such file or directory"), 127);
	else
		return (err_msg2(cmd_name, "command not found"), 127);
}

// handle the case when the command path is not found
// print an error message and exit with the appropriate exit code
static void	handle_no_path(t_data *data, int i)
{
	char	*cmd_name;
	int		exit_code;

	cmd_name = data->cmds[i]->cmd_array[0];
	if (is_directory(cmd_name) && ft_strchr(cmd_name, '/'))
	{
		err_msg2(cmd_name, "Is a directory");
		exit_code = 126;
	}
	else
		exit_code = handle_no_cmd_file(cmd_name);
	clean_up(data);
	close(0);
	close(1);
	exit(exit_code);
}

// handle the case when the command is empty or not found
static void	handle_empty_cmd(t_data *data, int i)
{
	t_cmd	*cmd;

	cmd = data->cmds[i];
	if (cmd->cmd_array[0][0] == '\0' && cmd->has_redir)
	{
		clean_up(data);
		close(0);
		close(1);
		exit(0);
	}
	if (cmd->cmd_path == NULL)
		handle_no_path(data, i);
}

// child process, execute the command if possible, otherwise exit
void	child_process(t_data *data, int i)
{
	t_cmd	*cmd;
	int		exit_code;

	cmd = data->cmds[i];
	exit_code = 0;
	if (set_redirections(data, i) == ERROR)
	{
		close_pipes(data);
		clean_up(data);
		exit(1);
	}
	close_pipes(data);
	handle_empty_cmd(data, i);
	sig_cases(CHILD);
	close(data->fd_stdin);
	close(data->fd_stdout);
	execve(cmd->cmd_path, cmd->cmd_array, data->env);
	exit_code = handle_no_cmd_file(cmd->cmd_path);
	clean_up(data);
	exit(exit_code);
}
