/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_utills.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:36 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/12 08:47:02 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
