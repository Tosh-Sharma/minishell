/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:13:53 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/14 19:19:59 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_with_nl(char *input, char *joiner)
{
	char	*temp;
	char	*result;

	temp = NULL;
	if (input != NULL)
	{
		temp = input;
		result = ft_strjoin(temp, "\n");
		free(temp);
		temp = result;
	}
	result = ft_strjoin(temp, joiner);
	free(temp);
	free(joiner);
	return (result);
}

void	read_with_delimiter(char *delimiter, int file_fd)
{
	char	*input;
	char	*result;

	result = NULL;
	while (1)
	{
		input = readline(">");
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		else
		result = join_with_nl(result, input);
	}
	write(file_fd, result, ft_strlen(result));
}

void	heredoc(char *delimiter)
{
	int	file_fd;

	file_fd = open("input.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	read_with_delimiter(delimiter, file_fd);
	close(file_fd);
	file_fd = open("input.txt", O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
}

void	read_from_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		perror_and_exit("Could not open file.", 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
