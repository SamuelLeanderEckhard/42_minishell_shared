/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:36 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/11 10:20:17 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free all allocated memory in the cmds array
void clean_up_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i]->cmd_array)
			ft_free_str_arr(cmds[i]->cmd_array);
		if (cmds[i]->cmd_path)
			free(cmds[i]->cmd_path);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

// free all allocated memory
void	clean_up(t_data *data)
{
	if (data)
	{
		if (data->env)
			ft_free_str_arr(data->env);
		if (data->line)
			free(data->line);
		if (data->line_split)
			ft_free_str_arr(data->line_split);
		if (data->cmd_paths)
			ft_free_str_arr(data->cmd_paths);
		if (data->cmds)
			clean_up_cmds(data->cmds);
	}
}