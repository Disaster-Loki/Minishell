/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:47:15 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 16:41:13 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_help_righ(t_shell *sh, int *fd, int *i)
{
	while (sh->manager.file[*i])
	{
		if (!ft_strncmp(sh->manager.redir[*i], ">>", 2)
			&& ft_strlen(sh->manager.redir[*i]) == 2)
			*fd = open(sh->manager.file[*i], O_CREAT
					| O_WRONLY | O_APPEND, 0644);
		else if (!ft_strncmp(sh->manager.redir[*i], ">", 1)
			&& ft_strlen(sh->manager.redir[*i]) == 1)
			*fd = open(sh->manager.file[*i], O_CREAT
					| O_WRONLY | O_TRUNC, 0644);
		if (sh->manager.file[*i + 1])
			close(*fd);
		(*i)++;
	}
}

int	help_right(t_shell *sh, int *fd)
{
	int	i;

	i = 0;
	help_help_righ(sh, fd, &i);
	free_mat(sh->manager.redir);
	free_mat(sh->manager.file);
	if (*fd < 0)
	{
		xprint("bash: ", sh->manager.file[i - 1], 2);
		xprint(": ", "", 2);
		perror("");
		return (0);
	}
	return (1);
}

void	right_oper(t_shell *sh)
{
	int	pid;
	int	fd;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		if (!help_right(sh, &fd))
			return ;
		dup2(fd, STDOUT_FILENO);
		sh->redirect = 1;
		check_command(sh);
		close(fd);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	exec_right(t_shell *sh)
{
	sh->manager.control = 1;
	allocater(sh);
	get_dir(sh);
	get_file(sh);
	get_arg(sh);
	right_oper(sh);
	free_mat(sh->manager.redir);
	free_mat(sh->manager.file);
}
