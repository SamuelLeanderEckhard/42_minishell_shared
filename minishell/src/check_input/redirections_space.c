/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:37:54 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/28 18:56:39 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// surround first 'substr' with spaces in 'str' starting at index 'start_i'
// return ERROR or OK
// example: ("hello>>file", ">>", 5) -> "hello >> file"
int	surround_with_spaces(t_data *data, char *substr, int start_i)
{
	char	*temp;
	char	*new_substr;

	if (!ft_strnstr(data->line + start_i, substr, 2))
		return (ERROR);
	temp = ft_strjoin(" ", substr);
	if (!temp)
		return (ERROR);
	new_substr = ft_strjoin(temp, " ");
	free(temp);
	if (!new_substr)
		return (ERROR);
	data->line = ft_strreplace(data->line, substr, new_substr, start_i);
	free(new_substr);
	if (!data->line)
		return (ERROR);
	return (OK);
}

// part of separate_redirections, handle input redirections (<, <<)
// return ERROR or the index of space after the redirections
static int	separate_redirections_in(t_data *data, int i)
{
	if (data->line[i + 1] == '<')
	{
		if (data->line[i + 2] == '<' || data->line[i + 2] == '>')
			return (err_msg("syntax error"), ERROR);
		if (surround_with_spaces(data, "<<", i) == ERROR)
			return (ERROR);
		i += 3;
	}
	else
	{
		if (surround_with_spaces(data, "<", i) == ERROR)
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
		if (surround_with_spaces(data, ">>", i) == ERROR)
			return (ERROR);
		i += 3;
	}
	else
	{
		if (surround_with_spaces(data, ">", i) == ERROR)
			return (ERROR);
		i += 2;
	}
	return (i);
}

// separate redirections in the line
// example: ls>file -> ls > file
// return ERROR or the index of space after the redirections
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
