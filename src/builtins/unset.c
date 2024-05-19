/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:14:40 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/12 10:37:39 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the environment variable name is valid
// (only letters and underscores are allowed, cannot start with a digit)
static int	check_var_name(char *var_name, t_data *data)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && ft_isdigit(var_name[i]))
		{
			data->exit_status = 1;
			return (err_msg3("unset", var_name, "not a valid identifier"),
				ERROR);
		}
		else if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
		{
			data->exit_status = 1;
			return (err_msg3("unset", var_name, "not a valid identifier"),
				ERROR);
		}
		i++;
	}
	if (i == 0)
	{
		data->exit_status = 1;
		return (err_msg3("unset", var_name, "not a valid identifier"), ERROR);
	}
	return (OK);
}

// check if there is a flag after the unset command
// (our minishell does not support flags for the unset command)
static int	check_flag(char *var_name, int j, t_data *data)
{
	char	*substr;

	substr = NULL;
	if (j == 1 && var_name[0] == '-' && var_name[1])
	{
		substr = ft_substr(var_name, 0, 2);
		if (substr == NULL)
			err_msg("ft_substr failed");
		err_msg3("export", substr, "invalid option");
		data->exit_status = 2;
		free(substr);
		return (ERROR);
	}
	return (OK);
}

// handle the unset command
// if the environment variable is valid, remove it from data->env
static int	handle_unset(t_data *data, int j, char *var_name)
{
	int	index;

	var_name = remove_quotes(var_name);
	if (check_flag(var_name, j, data) == ERROR)
		return (ERROR);
	if (check_var_name(var_name, data) == ERROR)
		return (OK);
	index = ms_getenv_index(data, var_name);
	if (index == ERROR)
		return (OK);
	free(data->env[index]);
	while (data->env[index + 1])
	{
		data->env[index] = data->env[index + 1];
		index++;
	}
	data->env[index] = NULL;
	return (OK);
}

// remove the environment variable from the data structure env
void	ms_unset(t_data *data, int i)
{
	char	**unset_arg;
	int		j;

	data->exit_status = 0;
	unset_arg = data->cmds[i]->cmd_array;
	j = 1;
	if (i == 0 && data->cmd_count == 1)
	{
		while (unset_arg[j])
		{
			if (handle_unset(data, j, unset_arg[j]) == ERROR)
				return ;
			j++;
		}
	}
}
