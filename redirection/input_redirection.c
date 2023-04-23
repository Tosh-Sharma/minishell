/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:13:53 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/23 23:11:22 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_shell;

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
	char	*temp;

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
	temp = result;
	result = ft_strjoin(temp, "\n");
	free(temp);
	write(file_fd, result, ft_strlen(result));
}

void	heredoc_sigint_quit(int signum)
{
	(void)signum;
	if (g_shell.heredoc_fd != -1)
	{
		close(g_shell.heredoc_fd);
		g_shell.heredoc_fd = -1;
		exit(1);
	}
}

void	heredoc_special_sigint(int signum)
{
	(void)signum;
	printf("This is here doc special sigint\n");
	if (g_shell.heredoc_fd != -1)
	{
		close(g_shell.heredoc_fd);
		g_shell.heredoc_fd = -1;
		exit(1);
	}
}

void	forked_heredoc(char *delimiter)
{
	int	file_fd;
	int	id;

	printf("Its a forked heredoc\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, heredoc_special_sigint);
		file_fd = open("input.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		g_shell.heredoc_fd = file_fd;
		read_with_delimiter(delimiter, file_fd);
		close(file_fd);
	}
	waitpid(-1, NULL, 0);
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
	file_fd = open("input.txt", O_RDONLY);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
}

void	heredoc(char *delimiter, int is_piped)
{
	int	file_fd;

	if (is_piped == 0 && is_builtin_command(&g_shell) == 1)
		forked_heredoc(delimiter);
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_sigint_quit);
		file_fd = open("input.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		g_shell.heredoc_fd = file_fd;
		read_with_delimiter(delimiter, file_fd);
		close(file_fd);
		signal(SIGINT, handle_interrupt);
		file_fd = open("input.txt", O_RDONLY);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
}
