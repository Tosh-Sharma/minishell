/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:41 by tsharma           #+#    #+#             */
/*   Updated: 2023/01/28 02:14:15 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_incorrect_syntax(char *input)
{
}

void	perror_and_exit(char *input, int exit_code)
{
	perror(input);
	exit(exit_code);
}
