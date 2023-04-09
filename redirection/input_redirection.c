/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:13:53 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/09 18:47:40 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_with_delimiter(t_shell *shell, char *delimiter, int is_piped)
{
	char	*input;
	char	*result;
	char	*temp;

	result = NULL;
	temp = NULL;
	while (1)
	{
		input = readline(">");
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		else
		{
			temp = ft_strjoin(result, "");
			free(result);
			result = ft_strjoin(temp, input);
			free(temp);
			free(input);
		}
	}
}

void	read_from_file(t_shell *shell, char *file_name)
{
}
