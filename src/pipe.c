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

int	read_line2(t_shell *sh, char *str)
{
	sh->input = str;
	read_env(sh);
	sh->mt = ft_split(sh->input, ' ');
	if (!get_path(sh) || !check_command(sh))
		return (0);
	free_mat(sh->mt);
	return (1);
}

int	exec_cmd(t_shell *sh, char *cmd, int fd[2])
{
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		read_line2(sh, cmd);
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
	{
		free_mat(mt);
		return ;
	}
	i = -1;
	num_cmds = matrix_line(mt);
	while (++i < num_cmds)
	{
		pipe(fd);
		exec_cmd(sh, mt[i], fd);
	}
}
