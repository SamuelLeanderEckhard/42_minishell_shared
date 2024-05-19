/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:55:39 by seckhard          #+#    #+#             */
/*   Updated: 2024/04/25 16:38:36 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

// handle SIGINT signal (ctrl + c) in interactive mode
static void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = CTRL_C;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sig_quit(int signal)
{
	(void)signal;
	ft_printf("Quit (core dumped)\n");
	kill(0, SIGCHLD);
}

// handle SIGINT signal (ctrl + c) in heredoc
static void	heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = CTRL_C;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

// handle different signals (SIGINT - ctrl + c, SIGQUIT - ctrl + \)
void	sig_cases(int sig_status)
{
	if (sig_status == INTERACTIVE)
	{
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_status == NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, &sig_quit);
	}
	else if (sig_status == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (sig_status == HEREDOC)
	{
		signal(SIGINT, &heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
