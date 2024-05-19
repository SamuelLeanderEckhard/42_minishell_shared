/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:07:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/12 08:10:21 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// wrap the string in quotes
// 'str_p' is a pointer to the string that is wrapped in quotes
// 'quote' is the quote character that was found in the string
// return ERROR or OK
static int	wrap_in_quotes(char **str_p, char quote)
{
	char	*new_str;
	char	*outer_quote;

	if (quote == S_QUOTE)
		outer_quote = "\"";
	else
		outer_quote = "'";
	new_str = ft_strjoin(outer_quote, *str_p);
	if (!new_str)
		return (err_msg("ft_strjoin failed"), ERROR);
	free(*str_p);
	*str_p = ft_strjoin(new_str, outer_quote);
	if (!(*str_p))
		return (err_msg("ft_strjoin failed"), ERROR);
	free(new_str);
	return (OK);
}

// wrap special characters in quotes (<, >, <<, >>, |)
// part of replace_name_with_value()
static int	wrap_special_characters(char **str_p)
{
	int		i;
	char	temp[2];

	if (!*str_p)
		return (OK);
	i = 0;
	temp[0] = '\0';
	while ((*str_p)[i])
	{
		if ((*str_p)[i] == '<' || (*str_p)[i] == '>' || (*str_p)[i] == '|')
		{
			temp[0] = (*str_p)[i];
			temp[1] = '\0';
			if (surround_with(str_p, temp, "'", i) == ERROR)
				return (ERROR);
			i += 2;
		}
		if ((*str_p)[i])
			i++;
	}
	return (OK);
}

// get the value of the environment variable and return it
static char	*handle_value(char *var_name, t_data *data)
{
	char	*value;

	value = ms_getenv(var_name + 1, data);
	if (value)
		value = ft_strdup(value);
	if (ft_strchr(value, S_QUOTE))
		wrap_in_quotes(&value, S_QUOTE);
	else if (ft_strchr(value, D_QUOTE))
		wrap_in_quotes(&value, D_QUOTE);
	if (wrap_special_characters(&value) == ERROR)
		return (free(value), NULL);
	if (!value)
		value = ft_strdup("");
	if (!value)
		return (err_msg("ft_strdup failed"), NULL);
	return (value);
}

// replace environment variable name with its value
// 'var_name' is the name of the environment variable (with $ prefix)
// 'str_p' is a pointer to the string where the replacement is done
// 'i' is the index of '$'
// return the value of the environment variable, or NULL if malloc fails
// example: ($USER -> user) ($nonexistent -> "")
char	*replace_name_with_value(char *var_name, char **str_p, t_data *data,
	int i)
{
	char	*value;

	if (((*str_p)[i + 1] == S_QUOTE || (*str_p)[i + 1] == D_QUOTE))
		value = ft_strdup("");
	else if (ft_strcmp(var_name, "$") == 0)
		value = ft_strdup("$");
	else
		value = handle_value(var_name, data);
	*str_p = ft_strreplace(*str_p, var_name, value, i);
	if (!(*str_p))
		return (err_msg("ft_strreplace failed"), NULL);
	return (value);
}
