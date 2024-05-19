/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:14:19 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/11 11:43:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the current working directory
void	ms_pwd(t_data *data, int i)
{
	char	*pwd;
	char	*sub_str;

	sub_str = NULL;
	if (data->cmds[i]->cmd_array[1] != NULL)
	{
		if (data->cmds[i]->cmd_array[1][0] == '-')
		{
			sub_str = ft_substr(data->cmds[i]->cmd_array[1], 0, 2);
			err_msg3("pwd", sub_str, "invalid option");
			free(sub_str);
			data->exit_status = 2;
			return ;
		}
	}
	pwd = ms_getenv("PWD", data);
	if (!pwd)
	{
		data->exit_status = 1;
		return (err_msg2("pwd", "PWD not set"));
	}
	ft_printf_fd(STDOUT_FILENO, "%s\n", pwd);
	data->exit_status = 0;
}
