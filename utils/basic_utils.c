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

extern t_shell g_shell;

void	check_for_incorrect_syntax(char *input)
{
	(void)input;
}

void	perror_and_exit(char *input, int exit_code)
{
	perror(input);
	my_exit(exit_code);
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

void	nullify_string(char *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
}

void	free_strings(char **str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != NULL)
	{
		//printf("%d:%s\n", i, str[i]);
		free(str[i]);
	}
	free(str);
	str = NULL;
}
