/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:53:52 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/17 17:09:30 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the environment
void	ms_env(t_data *data, int i)
{
	int	j;

	j = 0;
	if (data->cmds[i]->cmd_array[1] != NULL)
	{
		data->exit_status = 1;
		return (err_msg2("env", "too many arguments"));
	}
	while (data->env[j])
		printf("%s\n", data->env[j++]);
	data->exit_status = 0;
}
