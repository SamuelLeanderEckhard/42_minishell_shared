/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:03:50 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 14:18:02 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirect input-output to fd_in, fd_out
int	set_redirections(t_data *data, int i)
{
	if (dup2(data->cmds[i]->fd_in, STDIN_FILENO) == -1)
		return (err_msg(strerror(errno)), ERROR);
	if (dup2(data->cmds[i]->fd_out, STDOUT_FILENO) == -1)
		return (err_msg(strerror(errno)), ERROR);
	return (OK);
}

// set fd_in and fd_out to default values (0, 1, or pipe fds)
static void	set_default_fds(t_data *data, int i)
{
	if (i == 0)
		data->cmds[i]->fd_in = 0;
	else
		data->cmds[i]->fd_in = data->pipes[i - 1][0];
	if (i < data->cmd_count - 1)
		data->cmds[i]->fd_out = data->pipes[i][1];
	else
		data->cmds[i]->fd_out = 1;
}

// check redirections ('<', '<<', '>', '>>') and set fd_in, fd_out accordingly
// return ERROR or OK
int	set_cmd_in_out(t_data *data, int i)
{
	int	j;

	j = 0;
	set_default_fds(data, i);
	if (i > 0
		&& (data->cmds[i - 1]->no_infile || data->cmds[i - 1]->no_outfile))
	{
		data->cmds[i]->fd_in = open("/dev/null", O_RDONLY);
		if (data->cmds[i]->fd_in == -1)
			return (err_msg("failed to open /dev/null"), ERROR);
	}
	while (data->command_split[i][j])
	{
		if (handle_input(data, i, j) == ERROR)
			return (ERROR);
		if (handle_output(data, i, j) == ERROR)
			return (ERROR);
		j++;
	}
	return (OK);
}
