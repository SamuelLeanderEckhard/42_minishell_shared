/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_data_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:12:41 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/12 09:53:35 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find the path to the command in PATH
// return 'path' if successful, otherwise return NULL
static char	*find_path(t_data *data, char *cmd_name)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	if (cmd_name[0] == '\0')
		return (NULL);
	while (data->cmd_paths[i])
	{
		temp = ft_strjoin(data->cmd_paths[i], "/");
		if (!temp)
			return (err_msg("ft_strjoin failed"), NULL);
		path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (!path)
			return (err_msg("ft_strjoin failed"), NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

// find the path to the command
// return 'path' if successful, otherwise return NULL
char	*get_cmd_path(t_data *data, int i)
{
	char	*cmd_name;
	char	*path;

	path = NULL;
	cmd_name = ft_strdup(data->cmds[i]->cmd_array[0]);
	if (cmd_name == NULL)
		return (err_msg("ft_strdup failed"), NULL);
	cmd_name = remove_quotes(cmd_name);
	if (is_directory(cmd_name))
		return (free(cmd_name), NULL);
	if (cmd_name[0] == '/' || cmd_name[0] == '.')
		return (cmd_name);
	if (access(cmd_name, F_OK) == 0 && !is_directory(cmd_name))
		return (cmd_name);
	if (data->cmd_paths == NULL)
		return (free(cmd_name), NULL);
	path = find_path(data, cmd_name);
	free(cmd_name);
	return (path);
}
