/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:13:57 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/23 21:19:26 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_to_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		perror_and_exit("Could not open the file.", 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	write_to_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror_and_exit("Could not open the file.", 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
