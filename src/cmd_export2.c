/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/17 10:53:07 by sde-carv         ###   ########.fr       */
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

void    add_var(char **env, char *var)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    env[i] = var;
    i++;
    env[i] = NULL;
}

void    cmd_export2(char **env, char **mt)
{
    int i;

    i = 1;
    while (mt[i])
    {
        add_var(env, mt[i]);
        i++;
    }
}