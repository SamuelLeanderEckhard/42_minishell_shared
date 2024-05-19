/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:19:28 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/11 11:33:13 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the path is a directory, return true or false
bool	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (true);
	return (false);
}

// check for valid token after redirection symbol
// return ERROR or OK
int	check_redir_after(char *str_after_redir)
{
	if (!str_after_redir)
		return (err_msg("syntax error"), ERROR);
	if (str_after_redir[0] == '>'
		|| str_after_redir[0] == '<')
		return (err_msg2("syntax error near unexpected token",
				str_after_redir), ERROR);
	return (OK);
}

// part of replace_envvars_in_str()
// skip the next word in the string
// 'str_p' is a pointer to the string where the replacement is done
// 'i' is the index of the first character of the current word
void	skip_next_word(char **str_p, int *i)
{
	while ((*str_p)[*i] && (*str_p)[*i] != ' ')
		(*i)++;
	while ((*str_p)[*i] && (*str_p)[*i] == ' ')
		(*i)++;
	while ((*str_p)[*i] && (*str_p)[*i] != ' ')
		(*i)++;
}

// get the name of the environment variable starting at index 'i' in the 'str'
// return the name of the environment variable with $ prefix
// return value has to be freed
char	*get_var_name(char *str, int i)
{
	int		j;
	char	*var_name;

	j = i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, i, j - i);
	return (var_name);
}

// surround first 'substr' with 'surround' in 'str' starting at index 'start_i'
// 'str' is a pointer to the string where the replacement is done
// return ERROR or OK
// example: ("hello>>file", ">>", " ", 5) -> "hello >> file"
int	surround_with(char **str, char *substr, char *surround, int start_i)
{
	char	*temp;
	char	*new_substr;

	if (!ft_strnstr(*str + start_i, substr, 2))
		return (ERROR);
	temp = ft_strjoin(surround, substr);
	if (!temp)
		return (ERROR);
	new_substr = ft_strjoin(temp, surround);
	free(temp);
	if (!new_substr)
		return (ERROR);
	*str = ft_strreplace(*str, substr, new_substr, start_i);
	free(new_substr);
	if (!*str)
		return (ERROR);
	return (OK);
}
