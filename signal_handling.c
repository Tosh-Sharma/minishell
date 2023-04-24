/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:45:43 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/24 13:13:37 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_shell;

void	handle_quit(int signum)
{
	pid_t	pid;

	(void)signum;
	if (g_shell.is_heredoc_active == 0)
	{
		pid = waitpid(-1, NULL, WNOHANG);
		if (pid != -1)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_shell.return_value = 131;
		}
	}
}

void	handle_interrupt(int signum)
{
	pid_t	pid;

	(void)signum;
	if (g_shell.is_heredoc_active == 1)
	{
		if (g_shell.split_com != NULL)
		{
			close(g_shell.heredoc_fd);
			g_shell.is_heredoc_active = 0;
			g_shell.heredoc_fd = -1;
		}
	}
	else
	{
		pid = waitpid(-1, 0, 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 0);
		if (pid == -1)
			rl_redisplay();
	}
}

void	signal_return_value(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == 13)
		g_shell.return_value = 0;
	else if (WIFEXITED(status))
		g_shell.return_value = WEXITSTATUS(status) + 128;
	else if (WIFSTOPPED(status))
		g_shell.return_value = WSTOPSIG(status) + 128;
}

void	main_signal_handling(void)
{
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
}
