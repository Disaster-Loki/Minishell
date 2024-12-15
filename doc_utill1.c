/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_utill1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:41:19 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 17:06:43 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_heredoc_delimiter(t_shell *sh)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (sh->mat[++i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			j++;
	}
	sh->manager.heredoc_delimiter = malloc(sizeof(char *) * (j + 1));
	if (!sh->manager.heredoc_delimiter)
		return ;
	i = -1;
	j = 0;
	while (sh->mat[++i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			sh->manager.heredoc_delimiter[j++] = ft_strdup(sh->mat[i + 1]);
	}
	sh->manager.heredoc_delimiter[j] = NULL;
}

void	two_positions(t_shell *sh)
{
	char	*temp;

	while (1)
	{
		temp = readline("> ");
		if (!temp)
			return ;
		if (!ft_strncmp(sh->mat[1], temp, ft_strlen(sh->mat[1]))
			&& temp[ft_strlen(sh->mat[1])] == '\0')
		{
			free(temp);
			break ;
		}
		free(temp);
	}
}

void	tree_positions2(t_shell *sh)
{
	int	pid;

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

void	tree_positions(t_shell *sh)
{
	int	pid;

	fill_heredoc_tree_position(sh);
	free_mat(sh->mat);
	sh->mat = sh->manager.doc_tree_position;
	pid = fork();
	if (pid == 0)
		exec_exit(sh);
	else
	{
		waitpid(pid, &sh->status, 0);
		sh->status = ft_status(sh->status);
	}
}
