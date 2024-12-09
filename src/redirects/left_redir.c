/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:49 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/09 09:08:56 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_type(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->mat[++i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			return (1);
	}
	return (0);
}

int	find_file(t_shell *sh)
{
	int	i;
	int	fd;

	i = 0;
	while (sh->mat[++i])
	{
		fd = open(sh->manager.left_file[i], O_RDONLY);
		if (fd < 0)
		{
			printf("bash: %s: No such file for directory\n", sh->mat[i]);
			return (0);
		}
	}
	return (1);
}

void	left_oper(t_shell *sh)
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
		if (!find_file(sh))
			return ;
		fd = open(sh->mat[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		sh->redirect = 1;
		check_command(sh);
		close(fd);
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	exec_left(t_shell *sh)
{
	char	**temp_mat;

	sh->manager.control = 1;
	if (find_type(sh) == 1)
		double_left(sh);
	else
	{
		temp_mat = sh->mat;
		get_left_file(sh);
		if (!find_file(sh))
			return ;
		left_oper(sh);
		free_mat(temp_mat);
	}
}
