/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:11:51 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 19:31:46 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// change to the home directory
static void	ms_cd_home(t_data *data)
{
	char	*home;
	char	*old_pwd;
	char	pwd[PATH_MAX];

	home = ms_getenv("HOME", data);
	old_pwd = ms_getenv("PWD", data);
	if (home == NULL)
		err_msg2("cd", "HOME not set");
	else if (chdir(home) == -1)
		err_msg2("cd", strerror(errno));
	getcwd(pwd, PATH_MAX);
	ms_setenv("OLDPWD", old_pwd, data);
	ms_setenv("PWD", pwd, data);
}

// change to the given directory
static void	ms_cd_path(t_data *data, int i)
{
	char	*path;
	char	*old_pwd;
	char	pwd[PATH_MAX];

	path = data->cmds[i]->cmd_array[1];
	old_pwd = ms_getenv("PWD", data);
	if (chdir(path) == -1)
		err_msg3("cd", path, strerror(errno));
	getcwd(pwd, PATH_MAX);
	ms_setenv("OLDPWD", old_pwd, data);
	ms_setenv("PWD", pwd, data);
}

// change directory
// works with relative and absolute paths
// if no arguments are given, or argument is '~', change to home directory
void	ms_cd(t_data *data, int i)
{
	if (i == 0 && data->cmd_count == 1)
	{
		if (data->cmds[i]->cmd_array[1] == NULL
			|| (ft_strcmp(data->cmds[i]->cmd_array[1], "~") == 0
			&& data->cmds[i]->cmd_array[2] == NULL))
			ms_cd_home(data);
		else if (data->cmds[i]->cmd_array[2])
			err_msg2("cd", "too many arguments");
		else
			ms_cd_path(data, i);
	}
	data->exit_status = 0;
}
