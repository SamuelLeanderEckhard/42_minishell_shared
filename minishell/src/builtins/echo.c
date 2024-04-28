/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:10:27 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/23 20:02:28 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the argument
static void	print_arg(char **echo_arg, int i, bool *newline, bool *check_flag)
{
	int	j;

	j = 1;
	echo_arg[i] = remove_quotes(echo_arg[i]);
	if (*check_flag && echo_arg[i][0] == '-')
	{
		while (echo_arg[i][j] == 'n')
			j++;
		if (echo_arg[i][j] == '\0' && j > 1)
		{
			*newline = false;
			return ;
		}
	}
	*check_flag = false;
	printf("%s", echo_arg[i]);
	if (echo_arg[i + 1])
		printf(" ");
}

// print the arguments of the echo command, handle the -n flag
void	ms_echo(t_data *data, int i)
{
	int		j;
	bool	newline;
	char	**echo_arg;
	bool	check_flag;

	j = 1;
	newline = true;
	echo_arg = data->cmds[i]->cmd_array;
	check_flag = true;
	while (echo_arg[j])
		print_arg(echo_arg, j++, &newline, &check_flag);
	if (newline)
		printf("\n");
	data->exit_status = 0;
}
