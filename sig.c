#include "minishell.h"

void	new_prompt(t_shell *mini)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	mini->sig = 0;
}
