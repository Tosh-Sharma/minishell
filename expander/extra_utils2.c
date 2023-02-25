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
    //printf("len var = %d\n", len);
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


--------------------------------------------------------------------------------------

/**
 * TODO: For Thomas,
 * Your job in replace env variable is to replace all environment
 * variables given as input with their value.
 * For example:
 * echo $USER ==> echo nameOfUser
 * echo $USER${USER} ==> echo nameOfUsernameOfUser
*/

char    *get_var(char *command, int nb, char *var, int len)
{
    int     j;
    int     k;

    j = 0;
    k = 0;
    if (nb != 0)
        j = nb;
    while (k < len)
    {
        if (command[j + 1] && (command[j + 1] == '{' 
            || command[j + 1] == '}' || command[j + 1] == ' '))
            j++;
        else
        {
            var[k] = command[j + 1];
            j++;
            k++;
        }
    }
    //printf("get_var k = : %d\n", k);
    var[k] = '\0';
    //printf("var :%s\n", var);
    return (var);
}

char    *replace_var(char *new_var, char *var, char *env_row)
{
    int     i;


    //First detect the position of = sign

    i = ft_strlen(var) + 1;
    //printf("R_V i = %d\n", i);
    //printf("len env_row = %d\n", (int)ft_strlen(env_row));
    new_var = (char *)malloc(sizeof(char) * ((ft_strlen(env_row)) + 1 - i));
    //printf("env_row[%d] = %c\n %s IS THE VQLUE", i, env_row[i], env_row);
    ft_strlcpy(new_var, &env_row[ft_strlen(var) + 1], ft_strlen(env_row) + 1 - i);
    //printf("new_var :%s\n", new_var);
    return (new_var);
}

int     new_len_com(char *command, char **res_var, int *positions)
{
    int i;
    int j;
    int p;
    int res;

    p = 0;
    res = 0;
    i = -1;
    while (command[++i])
    {
        //printf("command[%d] = %c\n", i, command[i]);
        if (i == positions[p])
        {
            i++;
            //printf("NLC command[%d] = %c\n", i, command[i]);
            //printf("NLC res_var[%d] :%s\n", p, res_var[p]);
            if (res_var[p] != NULL)
                //printf("NLC res_var[%d] len : %d\n", p, (int)ft_strlen(res_var[p]));
                res += (int)ft_strlen(res_var[p]);
            p++;
            //printf("res = %d\n", res);
            while (command[i + 1] && command[i + 1] != ' ' && command[i + 1] != '"' && i + 1 != positions[p])
                i++;
            //printf("POST WHILE command[%d] = %c\n", i, command[i]);
        }
        else
            //printf("command[%d] = %c\n", i, command[i]);
            res++;
    }
    printf("N_L_C res = %d\n", res + 1);
    return (res + 1);
}

char    *replace_com(char *res_com, char *command, char **res_var, int *positions)
{
    int     i;
    int     j;
    int     k;
    int     l;

    i = -1;
    j = -1;
    k = 0;
    //printf("replace_com com :%s\n", command);
    while (command[++i])
    {
        if (i == positions[k])
        {
            l = -1;
            //printf("res_var[k] :%s\n", res_var[k]);
            i++;
            //printf("R_C command[%d] = %c\n", i, command[i]);
            if (res_var[k] == NULL)
                k++;
            else
            {
                while (res_var[k][++l])
                    res_com[++j] = res_var[k][l];
                    //printf("%c\n", res_com[j]);
                printf("RESCOM :%s\n", res_com);
                k++;
            }
            while (command[i + 1] && command[i + 1] != ' ' && command[i + 1] != '"' && i + 1 != positions[k])
                i++;
        }
        else
            res_com[++j] = command[i];
           // printf("%c", res_com[j]);
    //    printf("\n");
    //    printf("i = %d\n", i);
    }
    res_com[++j] = '\0';
    return (res_com);
}

char	*replace_env_variable(char *command, int *positions, int count, t_shell *shell)
{
    char    *var;
    char    **res_var;
    int     i;
    int     j;
    int     k; 

    i = 0;
    j = 0;
    res_var = (char **)malloc(sizeof(char *) * (count));
    while (i < count)
    {
        if (positions[i] != 0)
            j = positions[i];
        //printf("positions[i] = : %d\n", positions[i]);
        //printf("j = : %d\n", j);
        if (command[j + 1] == '{')
            j++;
        k = 0;
        while(command[j + 1] && command[j + 1] != '"' && command[j + 1] != ' ' && command[j + 1] != '$' &&
            command[j + 1] != '}' && ++k)
            ++j;
        //var = (char *)malloc(sizeof(char) * k);
        //printf("\n");
        //printf("k : %d\n", k);
        var = (char *)malloc(sizeof(char) * (k + 1));
        get_var(command, positions[i], var, k);
        //printf("var post :%s\n", var);
        //printf("count : %d\n", count);
        j = 0;
        //printf("env_y = %d\n", shell->env_y);
        while (j < shell->env_y && join_and_cmp(var, shell->envp[j], ft_strlen(var)) != 0)
            j++;
        if (j == shell->env_y)
        {
            res_var[i] = NULL;
            //printf("NOT FOUND\n");
        }
        else
        {
            //printf("FOUND\n");
            res_var[i] = replace_var(res_var[i], var, shell->envp[j]);
        }
        //printf("res_var[%d] END :%s\n", i, res_var[i]);
        free(var);
        //printf("LA i = %d\n", i);
        i++;
    }
    //i++;
    //printf("ICI i = %d\n", i);
    res_var[i] = NULL;
    int kl = 0;
    //printf("PRELOOP\n");
    shell->res_com = (char *)malloc(sizeof(char) * new_len_com(command, res_var, positions));
    shell->res_com = replace_com(shell->res_com, command, res_var, positions);
    free(command);
    printf("FINAL :%s\n", shell->res_com);
    printf("FINAL LEN : %d\n", (int)ft_strlen(shell->res_com));
    return (shell->res_com);
}
