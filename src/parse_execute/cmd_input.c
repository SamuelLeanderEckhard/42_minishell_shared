/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:53:15 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/09 12:15:22 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set input redirection
// example: "grep a < input.txt"
// return ERROR or OK
static int	set_input(t_data *data, int i, int j)
{
	char	*file;

	if (data->cmds[i]->no_infile || data->cmds[i]->no_outfile)
		return (OK);
	if (check_redir_after(data->command_split[i][j + 1]) == ERROR)
		return (ERROR);
	file = remove_quotes(data->command_split[i][j + 1]);
	if (!file)
		return (err_msg("no input file after '<'"), ERROR);
	if (data->cmds[i]->fd_in > 0)
		reset_fd(data->cmds[i]->fd_in);
	data->cmds[i]->fd_in = open(file, O_RDONLY);
	if (data->cmds[i]->fd_in == -1)
	{
		data->cmds[i]->fd_in = open("/dev/null", O_RDONLY);
		if (data->cmds[i]->fd_in == -1)
			return (err_msg("failed to open /dev/null"), ERROR);
		if (data->cmds[i]->no_infile == false)
		{
			data->cmds[i]->no_infile = true;
			err_msg2(file, strerror(errno));
		}
	}
	return (OK);
}

// check if expansion is needed in here document
// if yes, return true, otherwise return false
static bool	check_expansion(t_data *data, int i, int j)
{
	char	*before;

	before = ft_strdup(data->command_split[i][j + 1]);
	if (!before)
		err_msg("ft_strdup failed");
	data->command_split[i][j + 1] = remove_quotes(
			data->command_split[i][j + 1]);
	if (ft_strcmp(before, data->command_split[i][j + 1]) != 0)
		return (free(before), true);
	free(before);
	return (false);
}

// loop for here document
static void	heredoc_loop(t_data *data, int i, int j, bool ignore_expansion)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == CTRL_C && g_signal--)
		{
			data->exit_status = 130;
			return (free(line));
		}
		if (!line)
			return (err_msg2("warning",
					"here-document delimited by end-of-file"));
		if (ft_strcmp(line, data->command_split[i][j + 1]) == 0)
			return (free(line));
		if (ignore_expansion == false)
			replace_envvars_in_str(data, &line, true);
		ft_printf_fd(data->cmds[i]->fd_in, "%s\n", line);
		free(line);
	}
}

// set here document redirection
// example: "grep a << EOF"
// return ERROR or OK
static int	set_heredoc(t_data *data, int i, int j)
{
	bool	ignore_expansion;

	ignore_expansion = false;
	if (check_redir_after(data->command_split[i][j + 1]) == ERROR)
		return (ERROR);
	if (data->cmds[i]->fd_in > 0)
		reset_fd(data->cmds[i]->fd_in);
	data->cmds[i]->fd_in = open("/tmp/heredoc",
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->cmds[i]->fd_in == -1)
		return (err_msg("failed to open /tmp/heredoc"), ERROR);
	ignore_expansion = check_expansion(data, i, j);
	sig_cases(HEREDOC);
	heredoc_loop(data, i, j, ignore_expansion);
	close(data->cmds[i]->fd_in);
	data->cmds[i]->fd_in = open("/tmp/heredoc", O_RDONLY);
	if (data->cmds[i]->fd_in == -1)
		return (err_msg("failed to open /tmp/heredoc"), ERROR);
	return (OK);
}

// handle input redirection ('<' or '<<')
// return ERROR or OK
int	handle_input(t_data *data, int i, int j)
{
	if (ft_strcmp(data->command_split[i][j], "<") == 0)
	{
		if (set_input(data, i, j) == ERROR)
			return (ERROR);
	}
	else if (ft_strcmp(data->command_split[i][j], "<<") == 0)
	{
		if (set_heredoc(data, i, j) == ERROR)
			return (ERROR);
	}
	return (OK);
}
