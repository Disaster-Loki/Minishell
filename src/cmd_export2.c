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

int check_var1(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    if (str[i] == '\0' && str[i - 1] != '=')
        return (0);
    return (1);
}

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function to add a new environment variable
void add_var(char ***env, char *str)
{
    int i;
    t_shell *hundler;
    char    *dup;

    hundler = malloc(sizeof(t_shell));
    i = 0;
    dup = strdup(str);
    while ((*env)[i])
        i++;
    hundler->temp_env = malloc(sizeof(char *) * (i + 2));
    i = -1;
    while ((*env)[++i])
        hundler->temp_env[i] = (*env)[i];
    hundler->temp_env[i] = dup;
    i++;
    hundler->temp_env[i] = NULL;
    *env = hundler->temp_env;
    free(hundler);
}

void    cmd_export2(char ***env, char **mt)
{
    if (mt[1]) 
    {
        add_var(env, mt[1]);
    }
}
