/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:37:54 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/09 19:32:53 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// part of separate_redirections, handle input redirections (<, <<)
// return ERROR or the index of space after the redirections
static int	separate_redirections_in(t_data *data, int i)
{
	if (data->line[i + 1] == '<')
	{
		if (data->line[i + 2] == '<' || data->line[i + 2] == '>')
			return (err_msg("syntax error"), ERROR);
		if (surround_with(&(data->line), "<<", " ", i) == ERROR)
			return (ERROR);
		i += 3;
	}
	else
	{
		if (surround_with(&(data->line), "<", " ", i) == ERROR)
			return (ERROR);
		i += 2;
	}
	return (i);
}

// part of separate_redirections, handle output redirections (>, >>)
// return ERROR or the index of space after the redirections
static int	separate_redirections_out(t_data *data, int i)
{
	if (data->line[i + 1] == '>')
	{
		if (data->line[i + 2] == '<' || data->line[i + 2] == '>')
			return (err_msg("syntax error"), ERROR);
		if (surround_with(&(data->line), ">>", " ", i) == ERROR)
			return (ERROR);
		i += 3;
	}
	else
	{
		if (surround_with(&(data->line), ">", " ", i) == ERROR)
			return (ERROR);
		i += 2;
	}
	return (i);
}

// separate redirections in the line starting at index 'i'
// example: (i = 2) ls>file -> ls > file (return 4)
// return ERROR or the index of space after the redirection symbol
int	separate_redirections(t_data *data, int i)
{
	if (data->line[i] == '<')
	{
		i = separate_redirections_in(data, i);
		if (i == ERROR)
			return (ERROR);
	}
	else
	{
		i = separate_redirections_out(data, i);
		if (i == ERROR)
			return (ERROR);
	}
	return (i);
}
