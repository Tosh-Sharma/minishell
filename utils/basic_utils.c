/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:41 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/01 12:02:58 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * TODO: There are a few things that we need to check for.
 * 1. We need to check if someone inserted something like 
 * two pipes together -> ||
 * 2. We need to check for illegal syntax in inserting env variables
 * Example: `echo ${HOSTNAME` is illegal.
 * 3. Environment variable names get expanded irrespective of anything
 * but if they are stuck with another thing without spaces, that should be
 * illegal or command not found. This is worth noting.
 * TODO: Keep looking for more and more illegal stuff.
*/
void	check_for_incorrect_syntax(char *input)
{
}

void	perror_and_exit(char *input, int exit_code)
{
	perror(input);
	exit(exit_code);
}
