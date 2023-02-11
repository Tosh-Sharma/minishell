#include "../minishell.h"

int get_len_var(char *command, int pos)
{
    int     len;

    len = 0;
    while (command[pos + 1] && command[pos + 1] == '"' && command[pos + 1] == '{')
        pos++;
    while (command[pos + 1] && command[pos + 1] != '"' && command[pos + 1] != '}' 
        && command[pos + 1] != ' ')
    {
        len++;
        pos++;
    }
    printf("len var = %d\n", len);
    return (len);
}

char    *get_var(char *command, int pos, int len)
{
    int     j;
    int     k;
    char    *var;

    j = 0;
    k = 0;
    var = (char *)malloc(sizeof(char) * (len + 1));
    while (command[pos + 1] && command[pos + 1] == '"' && command[pos + 1] == '{')
        pos++;
    while (k < len)
    {
        var[k] = command[pos + 1];
        pos++;
        k++;
    }
    //printf("get_var k = : %d\n", k);
    var[k] = '\0';
    printf("get_var :%s\n", var);
    return (var);
}

char    *replace_var(char *var, char *env_row)
{
    int     i;


    //First detect the position of = sign

    i = ft_strlen(var) + 1;
    printf("R_V i = %d\n", i);
    printf("len env_row = %d\n", ft_strlen(env_row));
    new_var = (char *)malloc(sizeof(char) * ((ft_strlen(env_row)) + 1 - i));
    printf("env_row[%d] = %c\n %s IS THE VQLUE", i, env_row[i], env_row);
    ft_strlcpy(new_var, &env_row[ft_strlen(var) + 1], ft_strlen(env_row) + 1 - i);
    printf("new_var :%s\n", new_var);
    return (new_var);
}

/**
 * Break the string one index before the first $.
 * Replace the dollar with the value from replace_var
 * str_join and free old and iterate.
*/
void    break_and_join_with_results(command, count, positions, var)
{
}

void    replace_env_variable(char *command, int *positions, int count, t_shell *shell)
{
    char    *res;
    int     i;
    int     j;
    char    **var;

    i = -1;
    j = 0;
    var = (char **)malloc(sizeof(char *) * (count));
    while (++i < count)
    {
        if (positions[i] != 0)
            j = positions[i];
        var[i] = get_var(command, j, get_len_var(command, j));
        printf("var[%d] :%s\n", i, var[i]);
        var[i] = replace_var(var[i], shell);
        //printf("env_var[%d] :%s\n", i, var[i]);
    }
    var[i] = NULL;
    //break_and_join_with_results(command, count, positions, var);
}
