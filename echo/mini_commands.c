#include "../minishell.h"

void    mini_pwd(void)
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
    int	flag_single;
	int	flag_double;

	flag_single = 0;
    printf("index = %d\n", index);
    printf("COM = %s\n", command);
    if (index < 0)
        write(1, "\n", 1);
    else
    {
        i = index;
        if (!(ft_strcmp(shell->split_com[1], "-n")))
        {
            shell->new_line_flag = 0;
            i += 2;
        }
        else
            i -= 1;
        while (command[i] == ' ')
                ++i;
        while (command[i])
        {
            printf("\ncommand[%d] = %c\n", i, command[i]);
            while (command[i] && command[i] != '"')
            {
                if ((command[i] == ' ' && command[i + 1] == ' '))
                    i++;
                else if (command[i] == '\'')
                {
                    while (command[++i] && command[i] != '\'')
                        ft_putchar_fd(command[i], 1);
                }
                else
                    ft_putchar_fd(command[i], 1);
                i++;
            }
            if (command[i] == '"')
            {
                while (command[++i] && command[i] != '"')
                    ft_putchar_fd(command[i], 1);   
            }
            i++;
        }
        if (shell->new_line_flag == 1)
            write(1, "\n", 1);
    }
}