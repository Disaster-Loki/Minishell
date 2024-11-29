/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/29 12:44:36 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_redir(char **mt)
{
	int	i;

	i = -1;
	while (mt[++i])
	{
		if ((!ft_strncmp(mt[i], ">", 1) && ft_strlen(mt[i]) == 1) || (!ft_strncmp(mt[i], ">>", 2) && ft_strlen(mt[i]) == 2))
			return (1);
	}
	return (0);
}

int find_right_oper(char **mat)
{
    int	i;

	i = -1;
	while (mat[++i])
	{
		if (mat[i][0] == '>')
			return (1);
	}
	return (0);
}

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

void  get_arg(t_shell *sh)
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

int check_built_in(t_shell *sh)
{
    if (!strcmp(sh->mat[0], "cd"))
        return (0);
    else if (!strcmp(sh->mat[0], "echo"))
        return (0);
    else if (!strcmp(sh->mat[0], "pwd"))
        return (0);
    else if (!strcmp(sh->mat[0], "env"))
        return (0);
    else if (!strcmp(sh->mat[0], "exit"))
        return (0);
    else if (!strcmp(sh->mat[0], "export"))
        return (0);
    else if (!strcmp(sh->mat[0], "unset"))
        return (0);
    return (1);
}

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
        if (!check_built_in(sh))
            check_command(sh);
        else
            exec_cmd(sh);
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