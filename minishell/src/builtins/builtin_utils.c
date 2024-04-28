/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:14:29 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/22 18:32:03 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create the environment variable 'env_var' from 'name' and 'value'
static char	*create_env_var(char *name, char *value)
{
	char	*env_var;
	char	*tmp;

	if (value == NULL)
	{
		env_var = ft_strdup(name);
		if (env_var == NULL)
			return (err_msg("ft_strdup failed"), NULL);
		return (env_var);
	}
	tmp = ft_strjoin(name, "=");
	if (tmp == NULL)
		return (err_msg("ft_strjoin failed"), NULL);
	env_var = ft_strjoin(tmp, value);
	free(tmp);
	if (env_var == NULL)
		return (err_msg("ft_strjoin failed"), NULL);
	return (env_var);
}

// duplicate env to new_env
static char	**dup_env(char **env, char **new_env, int env_len)
{
	int	j;

	j = 0;
	while (j < env_len)
	{
		new_env[j] = ft_strdup(env[j]);
		if (new_env[j] == NULL)
			return (err_msg("ft_strdup failed"), NULL);
		j++;
	}
	return (new_env);
}

// add a new environment variable to env
// (name=value or just name if value is NULL)
void	ms_addenv(char *name, char *value, t_data *data)
{
	char	**new_env;
	int		i;

	i = 0;
	while (data->env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (new_env == NULL)
		return (err_msg("malloc failed"));
	new_env = dup_env(data->env, new_env, i);
	new_env[i] = create_env_var(name, value);
	if (new_env[i] == NULL)
		return ;
	new_env[i + 1] = NULL;
	ft_free_str_arr(data->env);
	data->env = new_env;
}

// set the value of the environment variable 'name' to 'value'
// if the variable does not exist, do nothing
void	ms_setenv(char *name, char *value, t_data *data)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, len) == 0)
		{
			if (data->env[i][len] == '=')
			{
				free(data->env[i]);
				temp = ft_strjoin("=", value);
				if (temp == NULL)
					return (err_msg("ft_strjoin failed"));
				data->env[i] = ft_strjoin(name, temp);
				free(temp);
				if (data->env[i] == NULL)
					err_msg("ft_strjoin failed");
				return ;
			}
		}
		i++;
	}
}

// get the value of the environment variable 'name'
// return pointer to the value if it exists, NULL otherwise
char	*ms_getenv(char *name, t_data *data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, len) == 0)
		{
			if (data->env[i][len] == '=')
				return (data->env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
