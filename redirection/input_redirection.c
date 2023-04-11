/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:13:53 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/11 14:32:26 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(t_shell *shell, char *delimiter)
{
	int	file_fd;

	file_fd = open("input.txt", O_CREAT | O_WRONLY);
	read_with_delimiter(shell, delimiter, file_fd);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	unlink("input.txt");
}

void	read_with_delimiter(t_shell *shell, char *delimiter, int file_fd)
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
			temp = result;
			result = ft_strjoin(temp, input);
			free(temp);
			free(input);
		}
	}
	write(file_fd, result, ft_strlen(result));
}

void	read_from_file(t_shell *shell, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		perror_and_exit("Could not open file.", 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
