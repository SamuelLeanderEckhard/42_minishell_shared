/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:16:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/20 09:19:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the name of the environment variable starting at index 'i'
// return the name of the environment variable with $ prefix
// return value has to be freed
static char	*get_var_name(char *line, int i)
{
	int		j;
	char	*var_name;

	j = i + 1;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_' || line[j] == '?'))
		j++;
	var_name = ft_substr(line, i, j - i);
	return (var_name);
}

// replace environment variable name with its value
// 'line' is a pointer to the string where the replacement is done
// 'i' is the index of '$'
// return the value of the environment variable, or NULL if malloc fails
// example: ($USER -> user) ($nonexistent -> "")
static char	*replace_env_var(char *var_name, char **line, t_data *data, int i)
{
	char	*value;

	if (ft_strcmp(var_name, "$") == 0)
		value = ft_strdup("$");
	else
	{
		value = ms_getenv(var_name + 1, data);
		if (value)
			value = ft_strdup(value);
		if (!value)
			value = ft_strdup("");
		if (!value)
			return (err_msg("ft_strdup failed"), NULL);
	}
	*line = ft_strreplace(*line, var_name, value, i);
	if (!(*line))
		return (err_msg("ft_strreplace failed"), NULL);
	return (value);
}

// replace environment variable name with its value in double quotes
static int	handle_env_var_in_quotes(t_data *data, int *i, int *q_end)
{
	char	*var_name;
	char	*value;

	var_name = get_var_name(data->line, *i);
	value = replace_env_var(var_name, &(data->line), data, *i);
	if (value == NULL)
		return (free(var_name), ERROR);
	*i += ft_strlen(value) - 1;
	*q_end += ft_strlen(value) - ft_strlen(var_name);
	free(var_name);
	free(value);
	return (OK);
}

// replace environment variables with their values in double quotes
// return index of next double quote or index of null terminator
// example: echo "Hello $USER $PWD" -> echo "Hello user /home/user"
int	replace_env_variables_in_quotes(t_data *data, int q_start, int q_end)
{
	int		i;

	i = q_start;
	while (i < q_end)
	{
		if (data->line[i] == '$' && data->line[i + 1])
		{
			if (data->line[i + 1] == '?')
			{
				i = replace_exit_status(data, &(data->line), i, &q_end);
				if (i == ERROR)
					return (ERROR);
				continue;
			}
			handle_env_var_in_quotes(data, &i, &q_end);
		}
		i++;
	}
	return (q_end);
}

// this function is called when a '$' is found in the line,
// and replaces the environment variable or exit status with its value
// 'i' is the index of the '$'
// return index of last character of the value or ERROR
int	replace_env_variable(t_data *data, char **line_p, int i)
{
	char	*var_name;
	char	*value;
	char	*line;

	line = *line_p;
	if (line[i] == '$' && line[i + 1] == '?')
		return (replace_exit_status(data, line_p, i, 0));
	var_name = get_var_name(line, i);
	value = replace_env_var(var_name, line_p, data, i);
	if (value == NULL)
		return (free(var_name), ERROR);
	if (ft_strlen(value) == 0 && i == 0)
		i += ft_strlen(value);
	else
		i += ft_strlen(value) - 1;
	free(var_name);
	free(value);
	return (i);
}
