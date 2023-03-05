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

void    mini_echo_loop(char *command, int i)
{
    while (command[i])
        {
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
}

void    mini_echo(char *command, int index, t_shell *shell)
{
    int i;

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
        mini_echo_loop(command, i);
        if (shell->new_line_flag == 1)
            write(1, "\n", 1);
    }
}

void    env_count_update(t_shell *shell)
{
    int i;

    i = 0;
    while (shell->envp[i])
            i++;
    shell->env_y = i;
}

void    create_oldpwd(t_shell *shell, int flag)
{
    char    *pwd;
    char    *str;
    int     size;

    size = 100;
    pwd = NULL;
    pwd = getcwd(pwd, size);
    printf("flag = %d\n", flag);
    if (flag)
    {
        printf("FLAG\n");
        str = "unset OLDPWD";
        unset_command(shell, str);
    }
    printf("pwd =%s\n", pwd);
    str = "export OLDPWD=";
    str = ft_strjoin(str, pwd);
    export_command(shell, str);
}

void    change_pwd(t_shell *shell)
{
    char    *pwd;
    char    *str;
    int     size;

    size = 100;
    pwd = NULL;
    pwd = getcwd(pwd, size);
    str = "unset PWD";
    unset_command(shell, str);
    printf("pwd =%s\n", pwd);
    str = "export PWD=";
    str = ft_strjoin(str, pwd);
    export_command(shell, str);
}

void    pwd_refresh(t_shell *shell, char *new_dir)
{
    int i;

    i = 0;
    while (i < shell->env_y &&
        join_and_cmp("OLDPWD", shell->envp[i], 6) != 0)
        i++;
    printf("shell->envp[%d] :%s\n", i, shell->envp[i]);
    if (i == shell->env_y)
        create_oldpwd(shell, 0);
    else
        create_oldpwd(shell, 1);
}

void    mini_cd(char *command, t_shell *shell)
{
    int new_dir;
    int i;

    if (!shell->split_com[1])
        printf("not possible\n");
    else
    {
        env_count_update(shell);
        pwd_refresh(shell, shell->split_com[1]);
        if (!(new_dir = chdir(shell->split_com[1])))
            change_pwd(shell);
        else
            printf("dir not found\n");
    }
}