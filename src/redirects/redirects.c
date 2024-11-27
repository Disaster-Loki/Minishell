/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 15:03:22 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	input_redirect(char *str)
{
	return (ft_strcmp(str, "<") == 0);
}

int	redirect_operator(char *str)
{
	return (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0);
}

void	filter_tokens(char **mat)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mat[i])
	{
		if (redirect_operator(mat[i]) || input_redirect(mat[i]))
			i += 2;
		else
			mat[j++] = mat[i++];
	}
	mat[j] = NULL;
}
int	redirects(t_shell *sh)
{
	int	i;
	int	fd;

	i = 0;
	while (sh->mat[i])
	{
		if (redirect_operator(sh->mat[i]))
		{
			if (!sh->mat[i + 1])
				return (-1);
			fd = open(sh->mat[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
		else if (input_redirect(sh->mat[i]))
		{
			fd = open(sh->mat[i + 1], O_RDONLY);
			if (fd == -1)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
			i++;
		}
		i++;
	}
	return (0);
}
