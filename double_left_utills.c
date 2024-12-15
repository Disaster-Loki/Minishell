/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_utills.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:36 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 17:05:07 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_help_when_ordered1(t_shell *sh)
{
	int		i;
	char	*temp;

	i = 0;
	while (sh->manager.heredoc_delimiter[i + 1])
	{
		while (1)
		{
			temp = readline("> ");
			if (!temp)
				return ;
			if (!ft_strncmp(sh->manager.heredoc_delimiter[i], temp,
					ft_strlen(sh->manager.heredoc_delimiter[i]))
				&& temp[ft_strlen(sh->manager.heredoc_delimiter[i])] == '\0')
			{
				free(temp);
				break ;
			}
			free(temp);
		}
		i++;
	}
	free_mat(sh->manager.heredoc_delimiter);
}

void	help_when_ordered(t_shell *sh)
{
	int	pid;

	if (verify_status(sh))
		only_delimiter(sh);
	else
	{
		fill_heredoc_delimiter(sh);
		help_help_when_ordered(sh);
		fill_heredoc_delimiter2(sh);
		free_mat(sh->mat);
		sh->mat = sh->manager.heredoc_delimiter2;
		pid = fork();
		if (pid == 0)
			exec_exit(sh);
		else
		{
			waitpid(pid, &sh->status, 0);
			sh->status = ft_status(sh->status);
		}
		free_mat(sh->mat);
	}
}

void	help_when_orderd1(t_shell *sh)
{
	int	pid;

	fill_heredoc_delimiter(sh);
	help_help_when_ordered1(sh);
	fill_heredoc_delimiter2(sh);
	free_mat(sh->mat);
	sh->mat = sh->manager.heredoc_delimiter2;
	pid = fork();
	if (pid == 0)
		exec_exit(sh);
	else
	{
		waitpid(pid, &sh->status, 0);
		sh->status = ft_status(sh->status);
	}
}

void	when_unordered(t_shell *sh)
{
	help_when_unordered(sh);
	free_mat(sh->manager.heredoc_delimiter);
	fill_heredoc_arg(sh);
	free_mat(sh->mat);
	sh->mat = sh->manager.heredoc_arg;
	check_command(sh);
}

void	when_ordered(t_shell *sh)
{
	if (!ft_strncmp(sh->mat[0], "<<", 2) && ft_strlen(sh->mat[0]) == 2)
	{
		help_when_ordered(sh);
	}
	else
	{
		help_when_orderd1(sh);
	}
}
