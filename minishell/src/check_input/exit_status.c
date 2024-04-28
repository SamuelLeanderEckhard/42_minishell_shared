/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:23:55 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/20 07:41:14 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// replace exit status with its value
// return index of last character of the value or ERROR
int	replace_exit_status(t_data *data, char **line, int i, int *q_end)
{
	char	*value;
	int		ret;

	ret = i;
	value = ft_itoa(data->exit_status);
	if (!value)
		return (err_msg("ft_itoa failed"), ERROR);
	*line = ft_strreplace(*line, "$?", value, i);
	if (!(*line))
		return (err_msg("ft_strreplace failed"), ERROR);
	ret = i + ft_strlen(value) - 1;
	if (q_end)
		*q_end += ft_strlen(value) - 2;
	free(value);
	return (ret);
}
