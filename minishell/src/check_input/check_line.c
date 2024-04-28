/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/23 19:40:58 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the line has a syntax error
// return ERROR if it does, OK otherwise
static int	check_syntax(t_data *data)
{
	int		len;

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
	return (OK);
}

// check line beginnings and endings, check quotes, replace environment
// variables, replace '$?', and separate redirection symbols
int	check_line(t_data *data)
{
	if (check_syntax(data) == ERROR)
		return (ERROR);
	if (quotes_envvar_redir(data) == ERROR)
		return (ERROR);
	return (OK);
}
