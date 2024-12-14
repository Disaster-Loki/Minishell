/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_utills.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:36 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/14 11:03:04 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_double_left(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i++;
		else
		{
			sh->manager.left_double_file[j++] = sh->mat[i];
			i++;
		}
	}
	sh->manager.left_double_file[j] = NULL;
}

void	get_double_file(t_shell *sh)
{
	int	i;

	help_double_left(sh);
	i = 0;
	while (sh->manager.left_double_file[i])
		i++;
	sh->manager.left_double_file2 = malloc(sizeof(char *) * (i + 1));
	if (!sh->manager.left_double_file2)
		return ;
	i = -1;
	while (sh->manager.left_double_file[++i])
		sh->manager.left_double_file2[i]
			= ft_strdup(sh->manager.left_double_file[i]);
	sh->manager.left_double_file2[i] = NULL;
	free_mat(sh->mat);
	sh->mat = sh->manager.left_double_file2;
}

int	help_first_double_left(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i++;
		else
		{
			j++;
			i++;
		}
	}
	sh->manager.dell_double2 = malloc(sizeof(char *) * (j + 1));
	if (!sh->manager.dell_double2)
		return (0);
	return (1);
}

void	first_double_left(t_shell *sh)
{
	int		i;
	int		j;
	char	*temp;

	if (!help_first_double_left(sh))
		return ;
	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i++;
		else
			sh->manager.dell_double2[j++] = ft_strdup(sh->mat[i++]);
	}
	temp = sh->manager.dell_double2[0];
	sh->manager.dell_double2[0] = sh->manager.dell_double2[1];
	sh->manager.dell_double2[1] = temp;
	sh->manager.dell_double2[j] = NULL;
	free_mat(sh->mat);
	sh->mat = sh->manager.dell_double2;
}
