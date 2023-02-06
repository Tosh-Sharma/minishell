/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/06 23:37:46 by toshsharma       ###   ########.fr       */
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
	// TODO: Delete this. FOR TESTING ONLY.
	env_command(shell);
}
