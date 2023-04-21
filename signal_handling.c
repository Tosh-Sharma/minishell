/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:45:43 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/21 16:34:19 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_shell;

void	handle_quit(int signum)
{
	pid_t	pid;

	(void)signum;
	pid = waitpid(-1, NULL, WNOHANG);
	if (pid != -1 && g_shell.is_heredoc_active == 0)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_shell.return_value = 131;
	}
}

void	handle_interrupt(int signum)
{
	(void)signum;
	// write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_line_buffer[0] = '\0';
	rl_redisplay();
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
