/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/29 12:55:52 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void    right_oper(t_shell *sh) 
{
    int pid;
    int i;
    int fd;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return ;
    }
    if (pid == 0)
    {
        i = 0;
        while (sh->manager.file[i])
        {
            if (!ft_strncmp(sh->manager.redir[i], ">>", 2) && ft_strlen(sh->manager.redir[i]) == 2)
                fd = open(sh->manager.file[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
            else if (!ft_strncmp(sh->manager.redir[i], ">", 1) && ft_strlen(sh->manager.redir[i]) == 1)
                fd = open(sh->manager.file[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (sh->manager.file[i + 1])
                close(fd);
            i++;
        }
        if (fd < 0)
        {
            perror("open");
            return ;
        }
        dup2(fd, STDOUT_FILENO);
        sh->redirect = 1;
        check_command(sh);
        close(fd);
        exit(0);
    }
    else
        waitpid(pid, NULL, 0);
}

void    operators(t_shell *sh)
{
    sh->manager.control = 1;
    get_dir(sh);
    get_file(sh);
    get_arg(sh);
    right_oper(sh);
}