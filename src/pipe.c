/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:28:35 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/25 15:28:37 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_cmd(t_shell *sh, char *cmd, int fd[2])
{
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		sh->input = cmd;
		read_line(sh);
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
	return (0);
}

void	read_pipe(t_shell *sh)
{
	int		i;
	int		fd[2];
	char	**mt;
	int		num_cmds;

	mt = ft_split(sh->input, '|');
	if (mt[1] == NULL)
		return;

	i = -1;
	num_cmds = matrix_line(mt);
	while (++i < num_cmds - 1)
	{
		pipe(fd);
		exec_cmd(sh, mt[i], fd);
	}
	sh->input = mt[num_cmds - 1];
}

