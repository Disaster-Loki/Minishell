/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/23 11:16:01 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    write_until_equal(char *str)
{
    int i;

    i = 0;
    while (str[i] != '=')
    {
        printf("%c", str[i]);
        i++;
    }
    printf("%c", str[i]);
    printf("\"\"");
}

int check_var_w_value(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    if (str[i] == '\0' && str[i - 1] == '=')
        return (0);
    return (1);
}

void    add_var(char **env, char *str)
{
    int i;
    extern char **environ;
    static char   *temp_env[70000];

    printf("%s\n",  str);
    (void)env;
    i = -1;
    while (environ[++i])
        temp_env[i] = environ[i];
    temp_env[i] = str;
    temp_env[i + 1] = NULL;
    environ = temp_env;
}

void    cmd_export2(char **env, char **mt)
{

    add_var(env, mt[1]);
}