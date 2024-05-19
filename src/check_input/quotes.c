/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:19:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/28 07:58:24 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find next occurrence of 'quote' in 'str' starting at index 'i'
// return index of next 'quote' or index of null terminator
int	find_next_quote(char *str, int i, char quote)
{
	i++;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

// check if the line has unclosed quotes and separate redirection symbols
// return ERROR or OK
int	check_quotes_and_redirections(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == S_QUOTE || data->line[i] == D_QUOTE)
		{
			if (data->line[i] == S_QUOTE)
				i = find_next_quote(data->line, i, S_QUOTE);
			else if (data->line[i] == D_QUOTE)
				i = find_next_quote(data->line, i, D_QUOTE);
			if (!data->line[i])
				return (err_msg("unclosed quotes"), ERROR);
		}
		else if (data->line[i] == '<' || data->line[i] == '>')
		{
			i = separate_redirections(data, i);
			if (i == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (OK);
}

// remove necessary quotes from string, return the modified string
// example: test_"hello'world" -> test_hello'world
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	bool	in_s_quote;
	bool	in_d_quote;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	in_s_quote = false;
	in_d_quote = false;
	while (str[i])
	{
		if (str[i] == S_QUOTE && !in_d_quote)
			in_s_quote = !in_s_quote;
		else if (str[i] == D_QUOTE && !in_s_quote)
			in_d_quote = !in_d_quote;
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
