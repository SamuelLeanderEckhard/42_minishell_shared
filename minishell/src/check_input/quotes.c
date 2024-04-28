/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:19:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/19 20:17:58 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find next occurrence of 'quote' in 'data->line' starting at index 'i'
// replace environment variables with their values if in double quotes
// return index of next 'quote' or index of null terminator
static int	find_next_quote(t_data *data, int i, char quote)
{
	int		start;
	bool	has_env_var;
	char	*line;

	start = i;
	has_env_var = false;
	line = data->line;
	i++;
	while (line[i] && line[i] != quote)
	{
		if (line[i] == '$' && quote == D_QUOTE)
			has_env_var = true;
		i++;
	}
	if (has_env_var)
	{
		i = replace_env_variables_in_quotes(data, start, i);
		if (i == ERROR)
			return (ERROR);
	}
	return (i);
}

// check if the line has unclosed quotes,
// and replace environment variables in double quotes
static int	quotes(t_data *data, int i)
{
	if (data->line[i] == S_QUOTE)
	{
		i = find_next_quote(data, i, S_QUOTE);
		if (!data->line[i])
			return (err_msg("unclosed single quote"), ERROR);
	}
	else if (data->line[i] == D_QUOTE)
	{
		i = find_next_quote(data, i, D_QUOTE);
		if (!data->line[i])
			return (err_msg("unclosed double quote"), ERROR);
	}
	return (i);
}

// replace environment variables where necessary,
// and separate redirections with spaces
static int	envvar_redir(t_data *data, int i)
{
	if (data->line[i] == '$' && data->line[i + 1])
	{
		i = replace_env_variable(data, &(data->line), i);
		if (i == ERROR)
			return (err_msg("replace_env_variable failed"), ERROR);
	}
	else if (data->line[i] == '<' || data->line[i] == '>')
	{
		i = separate_redirections(data, i);
		if (i == ERROR)
			return (err_msg("separate_redirections failed"), ERROR);
	}
	return i;
}

// check if the line has unclosed quotes,
// replace environment variables where necessary,
// and separate redirections with spaces
// return ERROR, or OK if successful
int	quotes_envvar_redir(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		i = quotes(data, i);
		if (i == ERROR)
			return (ERROR);
		i = envvar_redir(data, i);
		if (i == ERROR)
			return (ERROR);
		i++;
	}
	return (OK);
}
