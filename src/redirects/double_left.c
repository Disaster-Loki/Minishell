/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:43 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/07 21:41:38 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_exit(t_shell *sh, int *fd)
{
	char	*temp;

	while (1)
	{
		temp = readline("> ");
		if (!temp)
			break ;
		if (!ft_strncmp(sh->mat[1], temp, ft_strlen(sh->mat[1]))
			&& temp[ft_strlen(sh->mat[1])] == '\0')
		{
			free(temp);
			break ;
		}
		write(*fd, temp, ft_strlen(temp));
		write(*fd, "\n", 1);
		free(temp);
	}
	free(sh->mat[1]);
	sh->mat[1] = ft_strdup("tmp");
	check_command(sh);
	close(*fd);
	unlink("tmp");
	exit(0);
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
