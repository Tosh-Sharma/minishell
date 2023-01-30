/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:45:43 by tsharma           #+#    #+#             */
/*   Updated: 2023/01/25 09:38:39 by tsharma          ###   ########.fr       */
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
 * TODO: Figure out how to handle CTRL + D as it is not a signal input
 * but a EOF input and it cannot be handled in the same way as our other inputs.
*/
void	signal_handling(void)
{
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, handle_quit);
}
