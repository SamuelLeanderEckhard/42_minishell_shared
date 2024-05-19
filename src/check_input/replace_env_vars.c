/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:16:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/12 08:09:26 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function is called when a '$' is found in the string,
// and replaces the environment variable or exit status with its value
// 'i' is the index of the '$'
// 'str_p' is a pointer to the string where the replacement is done
// return index of last character of the value in the string or ERROR
static int	replace_envvar(t_data *data, char **str_p, int i, int in_dq)
{
	char	*var_name;
	char	*value;

	if ((*str_p)[i + 1] == '?')
		return (replace_exit_status(data, str_p, i));
	else if ((*str_p)[i + 1] == D_QUOTE && in_dq)
		return (i);
	var_name = get_var_name(*str_p, i);
	if (!var_name)
		return (ERROR);
	value = replace_name_with_value(var_name, str_p, data, i);
	if (value == NULL)
		return (free(var_name), ERROR);
	if (ft_strlen(value) == 0 && i == 0)
		i += 0;
	else
		i += ft_strlen(value) - 1;
	free(var_name);
	free(value);
	return (i);
}

// go through the string and replace all environment variables with their values
// 'str_p' is a pointer to the string where the replacement is done
// 'in_h' is true if the string is in a here document, false otherwise
// return ERROR or OK
int	replace_envvars_in_str(t_data *data, char **str_p, bool in_h)
{
	int		i;
	bool	in_dq;
	bool	in_sq;

	i = 0;
	in_dq = false;
	in_sq = false;
	while ((*str_p)[i])
	{
		if (ft_strncmp(*str_p + i, "<<", 2) == 0 && !in_sq && !in_dq && !in_h)
			skip_next_word(str_p, &i);
		if ((*str_p)[i] == D_QUOTE && !in_sq)
			in_dq = !in_dq;
		else if ((*str_p)[i] == S_QUOTE && !in_dq)
			in_sq = !in_sq;
		else if ((*str_p)[i] == '$' && (*str_p)[i + 1] && !in_sq)
		{
			i = replace_envvar(data, str_p, i, in_dq);
			if (i == ERROR)
				return (ERROR);
		}
		if ((*str_p)[i])
			i++;
	}
	return (OK);
}
