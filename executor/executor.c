/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/07 02:37:00 by toshsharma       ###   ########.fr       */
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
// TODO: Delete this later. ONLY FOR TESTING.
void	execute_commands(t_shell *shell, char **splitted_commands)
{
	env_command(shell);
	printf("\n\nEXPORT COMMAND\n\n");
	export_command(shell, "export USER2=THOMAS USER3=THEO");
	printf("\n\nLAST ENV COMMAND\n\n");
	env_command(shell);
}
