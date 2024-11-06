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
	free(sh->input);
	free_mat(sh->mt);
	return (1);
}

void	exec_cmd(t_shell *sh, int *fd, int prev_fd, char *cmd)
{
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
	sh->input = ft_strtrim(cmd, " ");
	read_line(sh);
	exit(0);
}

void	init_vars(char **mt, int *fd, int *len, int *i)
{
	*i = -1;
	*fd = -1;
	*len = matrix_line(mt);
}

int	read_pipe(t_shell *sh)
{
	int		i;
	int		fd[2];
	int		prev_fd;
	char	**mt;
	int		num_cmds;

	mt = ft_split(sh->input, '|');
	if (!mt || !mt[1])
		return (free_mat(mt), 0);
	init_vars(mt, &prev_fd, &num_cmds, &i);
	while (++i < num_cmds)
	{
		if (i < num_cmds - 1)
			pipe(fd);
		if (fork() == 0)
			exec_cmd(sh, fd, prev_fd, mt[i]);
		if (prev_fd != -1)
			close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
	}
	while (wait(NULL) > 0)
		;
	return (free_mat(mt), 1);
}
