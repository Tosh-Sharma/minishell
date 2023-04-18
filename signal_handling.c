/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:45:43 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/01 20:27:24 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	handle_quit(int signum)
{
	printf("We got a signal %d\n", signum);
	exit(1);
}

void	handle_interrupt(int signum)
{
	printf("We got a signal %d\n", signum);
	exit(1);
}


/* void		handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		//ft_putchar_fd('\n', 1);
		new_prompt(&g_shell);
	}
	else if (signo == SIGQUIT)
	{
		printf("input :%s\n", g_shell.input);
		ft_putstr_fd("Quit: 3\n", 1);
		new_prompt(&g_shell);
		g_shell.return_value = 131;
	}
}*/

void	signal_return_value(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 13)
			g_shell.return_value = 0;
	}
	else if (WIFEXITED(status))
		g_shell.return_value = WEXITSTATUS(status) + 128;
	else if (WIFSTOPPED(status))
		g_shell.return_value = WSTOPSIG(status) + 128;
}

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("LA", 1);
			rl_on_new_line();
			rl_line_buffer[0] = '\0';
			free(g_shell.input);
			rl_redisplay();
		}
		else
		{
			ft_putchar_fd('\n', 1);
			g_shell.return_value = 130;
		}
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			ft_putchar_fd('\n', 1);
		else
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_shell.return_value = 131;
		}
	}
	//signal_return_value(status);
}

/**
 * SIGINT = CTRL + C
 * SIGQUIT = CTRL + \
 * TODO: SIGINT is just SIGQUIT right now. We need to implement SIGINT.
 * Thomas has some code that he has written for this. This uses the readline
 * library functions. REFERENCE: new_prompt().
 * TODO: Figure out how to handle CTRL + D as it is not a signal input
 * but a EOF input and it cannot be handled in the same way as our other inputs.
*/
void	signal_handling(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
