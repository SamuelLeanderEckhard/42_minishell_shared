/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:37:09 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/23 19:26:31 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

// Define return values
# define OK 0
# define ERROR -1

// Define the maximum path length
# define PATH_MAX 2048

// Define special characters
# define S_QUOTE '\''
# define D_QUOTE '\"'

// Define ANSI color escape codes
# define NEON "\x1b[38;5;190m"
# define RED "\x1b[31m"
# define RESET "\e[0m"

// Define mode
# define INTERACTIVE 0
# define NON_INTERACTIVE 1
# define CHILD 2
# define HEREDOC 3

// Signals
# define CTRL_C 1

// Define error messages
# define ARGS_ERROR RED "error:" RESET " minishell cannot take any arguments\n"

// Define the prompt
# define PROMPT NEON "minishell$ " RESET

extern int	g_signal;

// Define the command structure
typedef struct s_cmd
{
	char	**cmd_array; // {"ls", "-l", NULL}
	char	*cmd_path; // "/bin/ls"
	int		fd_in; // fd to read from
	int		fd_out; // fd to write to
	bool	no_infile; // true if couldn't open input file
	bool	no_outfile; // true if couldn't open output file
}	t_cmd;

// Define the main data structure
typedef struct s_data
{
	char	**env; // copy of the environment
	char	*line; // "ls -l | sort | grep a > output.txt"
	char	**line_split; // split by "|" {"ls -l", "sort", "grep a > output.txt"}
	char	***command_split; // split by " " {{ls, -l, NULL}, {sort, NULL}, {grep, a, >, output.txt, NULL}}
	char	**cmd_paths; // array of paths to commands
	t_cmd	**cmds; // array of commands
	int		**pipes; // array of pipes to connect commands
	pid_t	*pids; // array of child process ids
	int		cmd_count; // 3 (number of commands in the line)
	int		pipe_count; // 2 (number of pipes in the line)
	int		exit_status;
	int		fd_stdin; // copy of stdin
	int		fd_stdout; // copy of stdout
}	t_data;

// Function prototypes
/* ****************************************************************** General */
// File: src/init.c
int		init(t_data *data, char *env[]);
// File: src/main.c
int		main(int argc, char *argv[], char *env[]);
// File: src/signal.c
void 	sig_cases(int sig_status);

/* ************************************************************** Check input */
// File: src/check_input/check_line.c
int		check_line(t_data *data);
// File: src/check_input/env_variables.c
int		replace_env_variables_in_quotes(t_data *data, int q_start, int q_end);
int		replace_env_variable(t_data *data, char **line, int i);
// File: src/check_input/exit_status.c
int		replace_exit_status(t_data *data, char **line, int i, int *q_end);
// File: src/check_input/quotes.c
int		quotes_envvar_redir(t_data *data);
// File: src/check_input/redirections_space.c
int		separate_redirections(t_data *data, int i);

/* ******************************************************** Parse and execute */
// File: src/parse_execute/cmd_data.c
int		set_cmd_data(t_data *data, int i);
// File: src/parse_execute/cmd_in_out.c
int		set_redirections(t_data *data, int i);
int		set_cmd_in_out(t_data *data, int i);
// File: src/parse_execute/cmd_input.c
int		handle_input(t_data *data, int i, int j);
// File: src/parse_execute/cmd_output.c
int		handle_output(t_data *data, int i, int j);
// File: src/parse_execute/execute.c
int		execute_command(t_data *data, int i);
// File: src/parse_execute/handle_commands.c
int		handle_commands(t_data *data);
// File: src/parse_execute/init_2.c
int		init_2(t_data *data);
// File: src/parse_execute/parse_execute.c
char	*remove_quotes(char *str);
int		parse_execute_line(t_data *data);
// File: src/parse_execute/pid.c
void	add_pid(t_data *data, pid_t pid);
void	wait_for_processes(t_data *data);

/* ***************************************************************** Builtins */
// ms stands for minishell
// File: src/builtins/builtin_utils_2.c
int		ms_getenv_index(t_data *data, char *var_name);
char	*get_env_name(char *env_var);
// File: src/builtins/builtin_utils.c
void	ms_addenv(char *name, char *value, t_data *data);
void	ms_setenv(char *name, char *value, t_data *data);
char	*ms_getenv(char *name, t_data *data);
// File: src/builtins/cd.c
void	ms_cd(t_data *data, int i);
// File: src/builtins/echo.c
void	ms_echo(t_data *data, int i);
// File: src/builtins/env.c
void	ms_env(t_data *data, int i);
// File: src/builtins/exit.c
void	ms_exit(t_data *data, int i);
// File: src/builtins/export.c
void	ms_export(t_data *data, int i);
// File: src/builtins/pwd.c
void	ms_pwd(t_data *data, int i);
// File: src/builtins/unset.c
void	ms_unset(t_data *data, int i);

/* ********************************************** Clean up and error handling */
// File: src/clean_up_2.c
void	reset_fd(int fd);
int		reset_stdin_out(t_data *data);
void	clean_up_loop(t_data *data);
// File: src/clean_up.c
void	close_pipes(t_data *data);
void	free_pipes(t_data *data);
void	clean_up_cmds(t_cmd **cmds);
void	clean_up(t_data *data);
// File: src/err_msg.c
void	err_msg(char *msg);
void	err_msg2(char *msg1, char *msg2);
void	err_msg3(char *msg1, char *msg2, char *msg3);

# endif