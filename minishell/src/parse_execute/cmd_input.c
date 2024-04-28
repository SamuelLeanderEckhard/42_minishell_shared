/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:53:15 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/24 11:13:13 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set input redirection
// example: "grep a < input.txt"
// return ERROR or OK
static int	set_input(t_data *data, int i, int j)
{
	char	*file;

	if (data->cmds[i]->no_infile)
		return (OK);
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

// replace environment variables in a line of a here document
static void	replace_env_variables_in_heredoc(t_data *data, char **line_p)
{
	int		i;

	i = 0;
	while (line_p[0][i])
	{
		if (line_p[0][i] == '$' && line_p[0][i + 1])
		{
			i = replace_env_variable(data, line_p, i);
			if (i == ERROR)
				return (err_msg("replace_env_variable failed"));
		}
		i++;
	}
}

// loop for here document
static void	heredoc_loop(t_data *data, int i, int j)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == CTRL_C && g_signal--)
		{
			data->exit_status = 130;
			free(line);
			break ;
		}
		if (!line)
		{
			err_msg2("warning", "here-document delimited by end-of-file");
			break ;
		}
		if (ft_strcmp(line, data->command_split[i][j + 1]) == 0)
		{
			free(line);
			break ;
		}
		replace_env_variables_in_heredoc(data, &line);
		ft_printf_fd(data->cmds[i]->fd_in, "%s\n", line);
		free(line);
	}
}

// set here document redirection
// example: "grep a << EOF"
// return ERROR or OK
static int	set_heredoc(t_data *data, int i, int j)
{
	if (!data->command_split[i][j + 1])
		return (err_msg("no delimiter after '<<'"), ERROR);
	if (data->cmds[i]->fd_in > 0)
		reset_fd(data->cmds[i]->fd_in);
	data->cmds[i]->fd_in = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->cmds[i]->fd_in == -1)
		return (err_msg("failed to open /tmp/heredoc"), ERROR);
	sig_cases(HEREDOC);
	heredoc_loop(data, i, j);
	sig_cases(NON_INTERACTIVE);
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
