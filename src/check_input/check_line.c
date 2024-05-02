/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/02 10:25:22 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if there are two pipe symbols after each other
// if there are return ERROR, otherwise return OK
static int	check_pipe_symbols(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == S_QUOTE)
			i = find_next_quote(data->line, i, S_QUOTE);
		else if (data->line[i] == D_QUOTE)
			i = find_next_quote(data->line, i, D_QUOTE);
		if (data->line[i] == '|')
		{
			i++;
			while (data->line[i] == ' ')
				i++;
			if (data->line[i] == '|')
			{
				data->exit_status = 2;
				return (err_msg("syntax error"), ERROR);
			}
		}
		if (data->line[i])
			i++;
	}
	return (OK);
}

// check if the line has a syntax error
// return ERROR if it does, OK otherwise
static int	check_syntax(t_data *data)
{
	int	len;

	len = ft_strlen(data->line);
	if (data->line[0] == '|' || data->line[len - 1] == '|'
		|| data->line[0] == ';' || data->line[len - 1] == ';'
		|| data->line[0] == '\\' || data->line[len - 1] == '\\'
		|| data->line[0] == '>' || data->line[len - 1] == '>'
		|| data->line[len - 1] == '<')
	{
		data->exit_status = 2;
		return (err_msg("syntax error"), ERROR);
	}
	if (check_pipe_symbols(data) == ERROR)
		return (ERROR);
	return (OK);
}

// split the line by pipes and spaces,
// and count the number of commands and pipes
// return ERROR if malloc fails, OK otherwise
static int	split_and_count(t_data *data)
{
	data->line_split = ft_split_quotes(data->line, '|');
	if (!data->line_split)
		return (ERROR);
	data->command_split = ft_split_quotes_2d(data->line_split, ' ');
	data->cmd_count = ft_arrlen(data->line_split);
	if (data->cmd_count < 1)
		data->pipe_count = 0;
	else
		data->pipe_count = data->cmd_count - 1;
	return (OK);
}

// remove quotes around the strings in the command_split array
static void	remove_quotes_around(t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	temp = NULL;
	i = 0;
	while (data->command_split[i])
	{
		j = 0;
		while (data->command_split[i][j])
		{
			temp = data->command_split[i][j];
			if (ft_strcmp(temp, "echo") == 0)
				break ;
			data->command_split[i][j] = remove_quotes(temp);
			j++;
		}
		i++;
	}
}

// check line beginnings and endings, check quotes, split up the line,
// replace environment variables, and remove necessary quotes
int	check_line(t_data *data)
{
	if (check_syntax(data) == ERROR)
		return (ERROR);
	if (check_quotes_and_redirections(data) == ERROR)
		return (ERROR);
	if (replace_envvars_in_str(data, &(data->line)) == ERROR)
		return (ERROR);
	if (split_and_count(data) == ERROR)
		return (ERROR);
	remove_quotes_around(data);
	// printf("line: %s\n", data->line); // for testing
	// for (int i = 0; i < data->cmd_count; i++) // for testing
	// 	printf("line_split[%d]: %s\n", i, data->line_split[i]); // for testing
	// for (int i = 0; i < data->cmd_count; i++) // for testing
	// {
	// 	for (int j = 0; data->command_split[i][j]; j++) // for testing
	// 		printf("command_split[%d][%d]: %s\n", i, j, data->command_split[i][j]); // for testing
	// }
	return (OK);
}
