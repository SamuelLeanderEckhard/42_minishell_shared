/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:13:47 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/23 19:11:38 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the environment in export with "declare -x" in front of each variable
static void	export_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		printf("declare -x %s\n", data->env[i++]);
}

// check if the environment variable is valid
// (only letters and underscores are allowed, cannot start with a digit)
static int	check_env_var(char *env_var, t_data *data)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
	{
		if (i == 0 && ft_isdigit(env_var[i]))
		{
			data->exit_status = 1;
			return (err_msg3("export", env_var, "not a valid identifier"),
				ERROR);
		}
		else if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
		{
			data->exit_status = 1;
			return (err_msg3("export", env_var, "not a valid identifier"),
				ERROR);
		}
		i++;
	}
	if (i == 0 && env_var[i] == '=')
	{
		data->exit_status = 1;
		return (err_msg3("export", env_var, "not a valid identifier"), ERROR);
	}
	return (OK);
}

// check if there is a flag after the export command
// (our minishell does not support flags for the export command)
static int	check_flag(char *env_var, int j, t_data *data)
{
	char	*substr;

	substr = NULL;
	if (j == 1 && env_var[0] == '-' && env_var[1])
	{
		substr = ft_substr(env_var, 0, 2);
		if (substr == NULL)
			err_msg("ft_substr failed");
		err_msg3("export", substr, "invalid option");
		data->exit_status = 2;
		free(substr);
		return (ERROR);
	}
	return (OK);
}

// handle the export command
// if the environment variable is valid, add it to the env or update it
static int	handle_export(t_data *data, int j, char *env_var)
{
	char	*name;
	char	*value;

	if (check_flag(env_var, j, data) == ERROR)
		return (ERROR);
	if (check_env_var(env_var, data) == ERROR)
		return (OK);
	name = get_env_name(env_var);
	if (ft_strchr(env_var, '=') == NULL)
		value = NULL;
	else
		value = ft_strchr(env_var, '=') + 1;
	if (ms_getenv_index(data, name) == ERROR)
		ms_addenv(name, value, data);
	else
	{
		ft_printf_fd(2, "name: %s\n", name);
		ms_setenv(name, value, data);
	}
	free(name);
	return (OK);
}

// export the environment variable to the data structure env
// example: export VAR_NAME=VAR_VALUE will add VAR_NAME=VAR_VALUE to the env
void	ms_export(t_data *data, int i)
{
	char	**export_arg;
	int		j;

	data->exit_status = 0;
	export_arg = data->cmds[i]->cmd_array;
	j = 1;
	if (export_arg[1] == NULL)
	{
		export_env(data);
		return ;
	}
	if (i == 0 && data->cmd_count == 1)
	{
		while (export_arg[j])
		{
			if (handle_export(data, j, export_arg[j]) == ERROR)
				return ;
			j++;
		}
	}
}
