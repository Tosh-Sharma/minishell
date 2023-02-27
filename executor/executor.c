/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/27 15:35:48 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * The execute_commands section gets the output of the parser.
 * This means the output is already parsed and expanded and is ready to 
 * be executed.
 * Currently, we will only be allowing execution of dummy functions in this
 * function. Namely env, export and unset.
*/
void	execute_commands(t_shell *shell, char **splitted_commands)
{
	(void)splitted_commands;
	// env_command(shell);
	printf("\n\nexport USER2=THOMAS\n\n");
	export_command(shell, "export USER2=THOMAS");
	env_command(shell);
	printf("\n\nexport USER3=THEO TEST=test\n\n");
	export_command(shell, "export USER3=THEO TEST=test");
	env_command(shell);
	printf("\n\nunset USER2\n\n");
	unset_command(shell, "unset USER2");
	env_command(shell);
	printf("\n\nunset USER3 TEST\n\n");
	unset_command(shell, "unset USER3 TEST");
	env_command(shell);
	// printf("\n\nexport TEST1=TEST1\n\n");
	// export_command(shell, "export TEST1=TEST1");
	// env_command(shell);
}
