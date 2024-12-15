/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:43 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 17:12:16 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_exec_exit2(t_shell *sh, int *fd)
{
	char	**temp_mat;

	temp_mat = malloc(sizeof(char *) * 3);
	if (!temp_mat)
		return ;
	temp_mat[0] = ft_strdup(sh->mat[0]);
	temp_mat[1] = ft_strdup(".#@!tmp!@#");
	temp_mat[2] = NULL;
	free_mat(sh->mat);
	sh->mat = temp_mat;
	check_command(sh);
	close(*fd);
	unlink(".#@!tmp!@#");
	exit(0);
}

void	exec_exit2(t_shell *sh, int *i)
{
	int		fd;
	char	*temp;

	fd = open(".#@!tmp!@#", O_CREAT | O_APPEND | O_WRONLY | O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
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
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(temp);
	}
	help_exec_exit2(sh, &fd);
}

void	exec_exit(t_shell *sh)
{
	int		i;
	char	*temp;

	i = 1;
	if (sh->mat[i + 1])
	{
		while (sh->mat[i + 1])
		{
			while (1)
			{
				temp = readline("> ");
				if (!temp)
					return ;
				if (!ft_strncmp(sh->mat[i], temp, ft_strlen(sh->mat[i]))
					&& temp[ft_strlen(sh->mat[i])] == '\0')
				{
					free(temp);
					break ;
				}
			}
			i++;
		}
	}
	exec_exit2(sh, &i);
}

void	double_left(t_shell *sh)
{
	if (!ft_strncmp(sh->mat[0], "<<", 2) && ft_strlen(sh->mat[0]) == 2)
		in_first_position(sh);
	else
		other_position(sh);
}
