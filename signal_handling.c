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
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, handle_quit);
}
