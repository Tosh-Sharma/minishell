#include "../minishell.h"

void    mini_pwd(char *command)
{
    char    *pwd;
    int     size;

    size = 100;
    pwd = NULL;
    pwd = getcwd(pwd, size);
    if (pwd)
    {
        ft_putstr_fd(pwd, 1);
        ft_putchar_fd('\n', 1);
    }
}

void    mini_echo(char *command, int index, t_shell *shell)
{
    int i;

    i = index;
    if (command[i] && command[i] == '-' && command[i + 1] == 'n' &&
        command[i + 2] == ' ')
    {
        shell->new_line_flag = 0;
        i += 2;
    }
    else
        i -= 1;
    while (command[++i])
    {
        if (command[i] != '"')
            ft_putchar_fd(command[i], 1);
    }
    if (shell->new_line_flag == 1)
        write(1, "\n", 1);
}