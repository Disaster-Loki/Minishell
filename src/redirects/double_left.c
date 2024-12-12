/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:43 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/12 11:36:23 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	help_exec_exit2(t_shell *sh, int *fd)
{
	char	**temp_mat;

	temp_mat = malloc(sizeof(char *) * 3);
	if (!temp_mat)
		return ;
	temp_mat[0] = ft_strdup(sh->mat[0]);
	temp_mat[1] = ft_strdup("tmp");
	temp_mat[2] = NULL;
	free_mat(sh->mat);
	sh->mat = temp_mat;
	check_command(sh);
	close(*fd);
	unlink("tmp");
	exit(0);
}

void	exec_exit2(t_shell *sh, char *temp, int *i, int *fd)
{
	while (1)
	{
		temp = readline("> ");
		if (!temp)
			break ;
		if (!ft_strncmp(sh->mat[*i], temp, ft_strlen(sh->mat[*i]))
			&& temp[ft_strlen(sh->mat[*i])] == '\0')
		{
			free(temp);
			break ;
		}
		write(*fd, temp, ft_strlen(temp));
		write(*fd, "\n", 1);
		free(temp);
	}
	help_exec_exit2(sh, fd);
}

void	exec_exit(t_shell *sh, int *fd)
{
	int		i;
	char	*temp;

	i = 1;
	(void)fd;
	while (sh->mat[i + 1])
	{
		while (1)
		{
			temp = readline("> ");
			if (!temp)
				break ;
			if (!ft_strncmp(sh->mat[i], temp, ft_strlen(sh->mat[i]))
				&& temp[ft_strlen(sh->mat[i])] == '\0')
			{
				free(temp);
				break ;
			}
		}
		i++;
	}
	exec_exit2(sh, temp, &i, fd);
}

void	double_left(t_shell *sh)
{
	int	pid;
	int	fd;

	get_double_file(sh);
	pid = fork();
	if (pid == 0)
	{	
		fd = open("tmp", O_CREAT | O_APPEND | O_WRONLY | O_RDONLY, 0777);
		if (fd == -1)
		{
			perror("Error opening file");
			exit(1);
		}
		exec_exit(sh, &fd);
	}
	else
		waitpid(pid, &sh->status, 0);
}
