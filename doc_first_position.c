/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_first_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:46:44 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 17:03:42 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_when_unordered(t_shell *sh)
{
	int		i;
	char	*temp;

	fill_heredoc_delimiter(sh);
	i = 0;
	while (sh->manager.heredoc_delimiter[i])
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
}

void	help_help_when_ordered(t_shell *sh)
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

void	only_delimiter(t_shell *sh)
{
	int		i;
	char	*temp;

	i = 0;
	fill_heredoc_delimiter(sh);
	while (sh->manager.heredoc_delimiter[i])
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
}

void	more_than_tree_positions(t_shell *sh)
{
	if (!verify_status2(sh))
	{
		when_unordered(sh);
	}
	else
	{
		when_ordered(sh);
	}
}

void	in_first_position(t_shell *sh)
{
	if (!sh->mat[2])
		two_positions(sh);
	else if (!sh->mat[3])
		tree_positions(sh);
	else
		more_than_tree_positions(sh);
}
