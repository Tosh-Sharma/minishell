/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:41 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/18 16:56:08 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern	t_shell	g_shell;

/** TODO: Need to write a syntax checker for illegal syntax. You can refuse 
 * to handle all terrible input BUT make sure you don't crash.
 * There are a few things that we need to check for.
 * 1. We need to check if someone inserted something like 
 * two pipes together -> ||
 * 2. We need to check for illegal syntax in inserting env variables
 * Example: `echo ${HOSTNAME` is illegal.
 * 3. Environment variable names get expanded irrespective of anything
 * but if they are stuck with another thing without spaces, that should be
 * illegal or command not found. This is worth noting.
 * 4. There are a bunch of $ signals we can potentially tackle.
*/
void	check_for_incorrect_syntax(char *input)
{
	(void)input;
}

void	perror_and_exit(char *input, int exit_code)
{
	perror(input);
	exit(exit_code);
}

void	*ft_malloc_checker(int type, int size)
{
	int		*n;
	char	*s;

	if (type == 0)
	{
		n = (int *)malloc(sizeof(int) * size);
		if (!n)
			perror_and_exit("Could not allocate memory", 1);
		return (n);
	}
	else
	{
		s = (char *)malloc(sizeof(char) * size);
		if (!s)
			perror_and_exit("Could not allocate memory", 1);
		return (s);
	}
}

void	free_strings(char **str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != NULL)
		free(str[i]);
	free(str);
	str = NULL;
}
