/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/24 14:37:38 by ptchipoc         ###   ########.fr       */
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
    {
        if (str[i] == '=')
            return (0);
        i++;
    }
    return (1);
}

int check_var2(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    if (str[i - 1] == '=')
        return (1);
    return (0);
}

void add_var1(char ***env, char *str)
{
    int i;
    t_shell *hundler;
    char    *dup;

    hundler = malloc(sizeof(t_shell));
    i = 0;
    dup = ft_strdup(str);
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

void add_var2(char ***env, char *str)
{
    int i;
    t_shell *hundler;
    char    *dup;

    hundler = malloc(sizeof(t_shell));
    i = 0;
    dup = ft_strdup(str);
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
    int i;

    i = 1;
    while (mt[i])
    {
        if (check_var1(mt[i]))
            add_var1(env, mt[i]);
        else if (check_var2(mt[i]))
        {
            add_var2(env, mt[i]);
        }
        i++;
    }
}