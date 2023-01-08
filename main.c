#include "minishell.h"

void	print_welcome(void)
{
	printf("\n%s--------------------------------------------------\n", CYAN);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s¦        Welcome Chopri, to T&T Minishell        ¦\n", WHITE);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s--------------------------------------------------\n\n", CYAN);
}

void	init_mini(t_shell *mini)
{
	mini->main_line = NULL;
	mini->sig = 0;
	printf("ICI\n");
	print_welcome();
}

void	get_line(t_shell* mini)
{
	char		*buf;
	int		size;
	char		*prompt;
	char		*cyan;
	char		*white;
	unsigned int	i;

	i = 0;
	size = 1000;
	buf = NULL;
	buf = getcwd(buf, size);
	cyan = ft_strdup(CYAN);
	white = ft_strdup(WHITE);
	prompt = ft_strjoin(cyan, buf);
	free(buf);
	prompt = ft_strjoin(prompt, white);
	free(white);
	prompt = ft_strjoin(prompt, " $ ");
	printf("PROMPT = %s\n", prompt);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	mini->main_line = readline(prompt);
	free(prompt);
}

int	main(void)
{
	t_shell	mini;

//	printf("ICI\n");
	init_mini(&mini);
	while (1)
	{
		get_line(&mini);
		if (mini.main_line)
		{
			if (ft_strlen(mini.main_line) != 0)
			{
				//command_split(&mini, mini.main_line);
				//free(...)
				break;
			}
			free(mini.main_line);
		}
		else
		{
			printf("quit\n");
			exit(0);
		}
	}
	return (0);
}
