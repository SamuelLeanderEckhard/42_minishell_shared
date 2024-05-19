/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:39:28 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/28 10:45:07 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// increment the SHLVL environment variable
static int	increment_shlvl(t_data *data)
{
	char	*shlvl_value;

	shlvl_value = ms_getenv("SHLVL", data);
	if (shlvl_value == NULL)
		ms_addenv("SHLVL", "1", data);
	else
	{
		shlvl_value = ft_itoa(ft_atoi(shlvl_value) + 1);
		if (shlvl_value == NULL)
			return (ERROR);
		ms_setenv("SHLVL", shlvl_value, data);
		free(shlvl_value);
	}
	return (OK);
}

// initialize data structure and its members
// return OK if successful, ERROR if not
int	init(t_data *data, char *env[])
{
	data->fd_stdin = dup(STDIN_FILENO);
	data->fd_stdout = dup(STDOUT_FILENO);
	data->env = ft_strdup_arr(env);
	if (!data->env)
		return (ERROR);
	data->line = NULL;
	data->line_split = NULL;
	data->command_split = NULL;
	data->cmd_paths = NULL;
	data->cmds = NULL;
	data->pipes = NULL;
	data->pids = NULL;
	data->cmd_count = 0;
	data->pipe_count = 0;
	data->exit_status = 0;
	if (increment_shlvl(data) == ERROR)
		return (ERROR);
	return (OK);
}
