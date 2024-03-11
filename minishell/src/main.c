/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:42:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/11 10:05:04 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	if (argc != 1 || argv[1] || !env)
		return (ft_printf_fd(2, ARGS_ERROR), ERROR);
	if (init(&data, env) == ERROR)
		return (clean_up(&data), ERROR);
}