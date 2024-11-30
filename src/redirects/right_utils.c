/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_utills.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/29 13:45:14 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void  get_file(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mat[++i])
    {
        if ((!ft_strncmp(sh->mat[i], ">", 1) && ft_strlen(sh->mat[i]) == 1) || (!ft_strncmp(sh->mat[i], ">>", 2) && ft_strlen(sh->mat[i]) == 2))
            sh->manager.file[j++] = ft_strdup(sh->mat[i + 1]);
    }
    sh->manager.file[j] = NULL;
}

void  get_dir(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mat[++i])
    {
        if ((!ft_strncmp(sh->mat[i], ">", 1) &&  ft_strlen(sh->mat[i]) == 1) || (!ft_strncmp(sh->mat[i], ">>", 2) && ft_strlen(sh->mat[i]) == 2))
            sh->manager.redir[j++] = ft_strdup(sh->mat[i]);
    }
    sh->manager.redir[j] = NULL;
}

void    help_get_arg(t_shell *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (sh->mat[i])
    {
        if ((!ft_strncmp(sh->mat[i], ">", 1) && ft_strlen(sh->mat[i]) == 1) || (!ft_strncmp(sh->mat[i], ">>", 2) && ft_strlen(sh->mat[i]) == 2))
        {
            i += 2;
        }
        else
        {
            sh->manager.arg[j++] = sh->mat[i];
            i++;
        }
    }
    sh->manager.arg[j] = NULL;
}

void  get_arg(t_shell *sh)
{
    int i;

    help_get_arg(sh);
    i = 0;
    while (sh->manager.arg[i])
        i++;
    sh->manager.arg2 = malloc(sizeof(char *) * (i + 1));
    if (!sh->manager.arg2)
        return ;
    i = -1;
    while (sh->manager.arg[++i])
        sh->manager.arg2[i] = ft_strdup(sh->manager.arg[i]);
    sh->manager.arg2[i] = NULL;
    free_mat(sh->mat);
    sh->mat = sh->manager.arg2;
    sh->manager.flag = 1;
}