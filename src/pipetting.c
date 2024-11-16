/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/14 11:24:21 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	read_line2(t_shell *sh, char *str)
{
	int	i;

	i = -1;
	sh->input = str;
	get_path(sh);
	pipetting(sh);
	sh->args = tokenize(sh, sh->input);
	expansion(sh);
	check_command(sh);
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	return (0);
}

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
	read_line2(sh, ft_strtrim(cmd, " "));
	free(tmp);
	exit(0);
}

void	init_vars(char **mt, int *fd, int *len, int *i)
{
	*i = -1;
	*fd = -1;
	*len = matrix_line(mt);
}

int	pipetting(t_shell *sh)
{
	int		i;
	int		fd[2];
	int		prev_fd;
	char	**mt;
	int		num_cmds;

	mt = ft_split(sh->input, '|');
	i = -1;
	while (mt[++i])
		printf("%s\n", mt[i]);
	//print_matrix(mt);
	if (!mt || !mt[1])
		return (free_mat(mt), 0);
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
