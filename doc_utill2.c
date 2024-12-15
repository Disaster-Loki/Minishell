/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_utill2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:53:01 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 17:06:38 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_fill_heredoc_arg(t_shell *sh, int i, int j)
{
	i = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i += 2;
		else
		{
			j++;
			i++;
		}
	}
	sh->manager.heredoc_arg = malloc(sizeof(char *) * (j + 2));
	if (!sh->manager.heredoc_arg)
		return ;
	i = 2;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i += 2;
		else
			sh->manager.heredoc_arg[j++] = ft_strdup(sh->mat[i++]);
	}
	sh->manager.heredoc_arg[j] = NULL;
}

void	help_fill_heredoc_arg2(t_shell *sh, int i, int j)
{
	sh->manager.heredoc_arg = malloc(sizeof(char *) * (j + 2));
	if (!sh->manager.heredoc_arg)
		return ;
	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i += 2;
		else
			sh->manager.heredoc_arg[j++] = ft_strdup(sh->mat[i++]);
	}
	sh->manager.heredoc_arg[j] = NULL;
}

void	fill_heredoc_arg(t_shell *sh)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
	{
		help_fill_heredoc_arg(sh, i, j);
		return ;
	}
	i = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i += 2;
		else
		{
			j++;
			i++;
		}
	}
	help_fill_heredoc_arg2(sh, i, j);
}

void	fill_heredoc_delimiter2(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->mat[i + 1])
		i++;
	sh->manager.heredoc_delimiter2 = malloc(sizeof(char *) * 3);
	if (!sh->manager.heredoc_delimiter2)
		return ;
	if (!ft_strncmp(sh->mat[0], "<<", 2) && ft_strlen(sh->mat[0]) == 2)
	{
		sh->manager.heredoc_delimiter2[0] = ft_strdup(sh->mat[2]);
		sh->manager.heredoc_delimiter2[1] = ft_strdup(sh->mat[i]);
		sh->manager.heredoc_delimiter2[2] = NULL;
	}
	else
	{
		sh->manager.heredoc_delimiter2[0] = ft_strdup(sh->mat[0]);
		sh->manager.heredoc_delimiter2[1] = ft_strdup(sh->mat[i]);
		sh->manager.heredoc_delimiter2[2] = NULL;
	}
}

void	fill_heredoc_tree_position(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->mat[i + 1])
		i++;
	sh->manager.doc_tree_position = malloc(sizeof(char *) * 3);
	if (!sh->manager.doc_tree_position)
		return ;
	sh->manager.doc_tree_position[0] = ft_strdup(sh->mat[2]);
	sh->manager.doc_tree_position[1] = ft_strdup(sh->mat[1]);
	sh->manager.doc_tree_position[2] = NULL;
}
