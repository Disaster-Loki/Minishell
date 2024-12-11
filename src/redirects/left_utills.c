/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_utills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:55 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/11 19:39:29 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	firsts_left_file(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<", 1) && ft_strlen(sh->mat[i]) == 1)
			j++;
		i++;
	}
	sh->manager.first_left_file = malloc(sizeof(char *) * (j + 1));
	j = 0;
	i = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<", 1) && ft_strlen(sh->mat[i]) == 1)
		{
			sh->manager.first_left_file[j] = ft_strdup(sh->mat[i + 1]);
			j++;
		}
		i++;
	}
	sh->manager.first_left_file[j] = NULL;
}

int	help_get_left_file1(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<", 1) && ft_strlen(sh->mat[i]) == 1)
			i++;
		else
		{
			i++;
			j++;
		}
	}
	sh->manager.left_file = malloc(sizeof(char *) * (j + 1));
	if (!sh->manager.left_file)
		return (0);
	return (1);
}

void	get_left_file1(t_shell *sh)
{
	int	i;
	int	j;
	
	if (!help_get_left_file1(sh))
		return ;
	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<", 1) && ft_strlen(sh->mat[i]) == 1)
			i += 2;
		else
			sh->manager.left_file[j++] = ft_strdup(sh->mat[i++]);
	}
	sh->manager.left_file[j] = NULL;
	sh->mat = sh->manager.left_file;
}

void	get_left_file2(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->mat[i])
		i++;
	sh->manager.left_file2 = malloc(sizeof(char *) * (3));
	if (!sh->manager.left_file2)
		return ;
	sh->manager.left_file2[0] = ft_strdup(sh->mat[0]);
	sh->manager.left_file2[1] = ft_strdup(sh->mat[i - 1]);
	sh->manager.left_file2[2] = NULL;
	sh->mat = sh->manager.left_file2;
}

int	is_redir(char *str)
{
	if (!ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		return (1);
	return (0);
}

int	is_word(char *str)
{
	if (is_redir(str))
		return (0);
	return (1);
}

int	verify_status(t_shell *sh)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (sh->mat[++i])
	{
		if (is_word(sh->mat[i]))
		{
			if (flag == 1)
				return (0);
			flag = 1;
		}
		else if (is_redir(sh->mat[i]))
		{
			if (flag == 2)
				return (0);
			flag = 2;
		}
	}
	return (1);
}