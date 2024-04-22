/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:11:51 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/22 13:41:04 by bszabo           ###   ########.fr       */
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
	{
		err_msg2("cd", "HOME not set");
		data->exit_status = 1;
		return ;
	}
	if (chdir(home) == -1)
	{
		err_msg2("cd", strerror(errno));
		data->exit_status = 1;
		return ;
	}
	getcwd(pwd, PATH_MAX);
	ms_setenv("OLDPWD", old_pwd, data);
	ms_setenv("PWD", pwd, data);
	data->exit_status = 0;
}

// change to the given directory
static void	ms_cd_path(t_data *data, char *path)
{
	char	*old_pwd;
	char	pwd[PATH_MAX];

	old_pwd = ms_getenv("PWD", data);
	if (chdir(path) == -1)
	{
		err_msg3("cd", path, strerror(errno));
		data->exit_status = 1;
		return ;
	}
	getcwd(pwd, PATH_MAX);
	ms_setenv("OLDPWD", old_pwd, data);
	ms_setenv("PWD", pwd, data);
	data->exit_status = 0;
}

// change directory
// works with relative and absolute paths
// if no arguments are given, or argument is '~', change to home directory
void	ms_cd(t_data *data, int i)
{
	char	*cd_arg;

	cd_arg = data->cmds[i]->cmd_array[1];
	cd_arg = remove_quotes(cd_arg);
	if (i == 0 && data->cmd_count == 1)
	{
		if (cd_arg == NULL || (ft_strcmp(cd_arg, "~") == 0
			&& data->cmds[i]->cmd_array[2] == NULL))
			ms_cd_home(data);
		else if (data->cmds[i]->cmd_array[2])
		{
			err_msg2("cd", "too many arguments");
			data->exit_status = 1;
		}
		else
			ms_cd_path(data, cd_arg);
	}
	if (access(cd_arg, F_OK) != 0)
	{
		err_msg3("cd", cd_arg, strerror(errno));
		data->exit_status = 1;
	}
}
