/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:37:09 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/10 12:36:53 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

// Define return values
# define OK 0
# define ERROR 1

// Define ANSI color escape codes
# define NEON "\x1b[38;5;190m"
# define RED "\x1b[31m"
# define RESET "\e[0m"

// Define error messages
# define ARGS_ERROR RED "error:" RESET " minishell cannot take any arguments\n"

// Define the prompt
# define PROMPT NEON "minishell$ " RESET

// Define the command structure
typedef struct s_cmd
{
	char	**cmd_array; // {"ls", "-l", NULL}
	char	*cmd_path; // "/bin/ls"
}	t_cmd;

// Define the main data structure
typedef struct s_data
{
	char	**env; // copy of the environment
	char	*line; // "ls -l | sort | grep a > output.txt"
	char	**line_split; // split by "|" {"ls -l", "sort", "grep a > output.txt"}
	char	**cmd_paths; // array of paths to commands
	t_cmd	*cmds; // array of commands
	int		exit_status;
}	t_data;

// Function prototypes
int	init(t_data *data, char *env[]);

# endif