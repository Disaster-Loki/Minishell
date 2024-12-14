/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipetting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:05:00 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd(t_shell *sh, int *fd, int prev_fd, char *cmd)
{
	char	*tmp;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (fd[1] != -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	tmp = sh->input;
	sh->input = ft_strtrim(cmd, " ");
	read_line(sh);
	if (sh->env)
		free_mat(sh->env);
	free(tmp);
	exit(0);
}

int	pipetting(t_shell *sh)
{
	int		i;
	int		fd[2];
	int		prev_fd;
	char	**mt;
	int		num_cmds;

	mt = full_split(sh, sh->input, '|');
	i = -1;
	if (!mt || !mt[1])
		return (0);
	init_vars(mt, &prev_fd, &num_cmds, &i);
	while (++i < num_cmds)
	{
		if (i < num_cmds - 1)
			pipe(fd);
		if (fork() == 0)
			cmd(sh, fd, prev_fd, mt[i]);
		if (prev_fd != -1)
			close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
	}
	while (waitpid(-1, &sh->status, 0) > 0)
		;
	return (free_mat(mt), 1);
}
