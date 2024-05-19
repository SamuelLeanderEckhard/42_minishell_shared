/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:27:38 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/25 18:31:24 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse the line, prepare data for execution
// return ERROR if any of the steps fail, OK otherwise
int	parse_execute_line(t_data *data)
{
	if (init_2(data) == ERROR)
		return (ERROR);
	if (handle_commands(data) == ERROR)
		return (ERROR);
	return (OK);
}
