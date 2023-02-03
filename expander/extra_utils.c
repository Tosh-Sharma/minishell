/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:32:08 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/01 12:26:45 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * TODO: For Thomas,
 * Your job in replace env variable is to replace all environment
 * variables given as input with their value.
 * For example:
 * echo $USER ==> echo nameOfUser
 * echo $USER${USER} ==> echo nameOfUsernameOfUser
*/

int     env_row_counter(t_shell *shell)
{
    int i;

    i = 0;
    while (shell->envp[i])
        i++;
    //printf("env_y = %d\n", i);
    return (i);
}

char    *get_var(char *command, int *positions, int nb, int len)
{
    char    *var;
    int     j;
    int     k;

    j = 0;
    k = 0;
    var = (char *)malloc(sizeof(char) * len + 1);
    if (positions[nb] != 0)
        j = positions[nb];
    while(k < len)
    {
        if (command[j + 1] == '{' || command[j + 1] == '}' || command[j + 1] == ' ')
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

void	replace_env_variable(char *command, int *positions, int count, t_shell *shell)
{
    char    *var;
    char    *res;
    int     i;
    int     j;
    int     k; 

    i = 0;
    j = 0;
    k = 0;
    var = NULL;
    shell->env_y = env_row_counter(shell);
    while (i < count)
    {
        if (positions[i] != 0)
            j = positions[i];
        //printf("positions[i] = : %d\n", positions[i]);
        //printf("j = : %d\n", j);
        k = 0;
        if (command[j + 1] == '{')
            j++;
        while(command[j + 1] && command[j + 1] != ' ' && command[j + 1] != '$' &&
            command[j + 1] != '}')
        {
            //printf("%c", command[j + 1]);
            k++;
            j++;
        }
        var = (char *)malloc(sizeof(char) * k);
        //printf("\n");
        //printf("k : %d\n", k);
        var = get_var(command, positions, i, k);
        //printf("var post :%s\n", var);
        j = 0;
        while (j < shell->env_y && ft_strncmp(var, shell->envp[j], ft_strlen(var)) != 0)
            j++;
        if (j == shell->env_y)
            res = NULL;
        else
            res = shell->envp[j] + ft_strlen(var) + 1;
        printf("%s ", res);
        i++;
    }
}
