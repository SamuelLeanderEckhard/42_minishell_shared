/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:22:41 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/28 10:50:48 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the index of the environment variable in the data structure env
// return ERROR if the variable is not found
int	ms_getenv_index(t_data *data, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, len) == 0)
		{
			if (data->env[i][len] == '=' || data->env[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (ERROR);
}

// get the name of the environment variable 'env_var'
// example: VAR_NAME=VAR_VALUE will return VAR_NAME
char	*get_env_name(char *env_var)
{
	int		i;
	char	*name;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	name = ft_substr(env_var, 0, i);
	if (name == NULL)
		err_msg("ft_substr failed");
	return (name);
}
