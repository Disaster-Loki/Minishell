/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_utills.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:35:55 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/09 08:59:00 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	help_file(t_shell *sh)
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
			sh->manager.left_file[j++] = sh->mat[i];
			i++;
		}
	}
	sh->manager.left_file[j] = NULL;
}

void	get_left_file(t_shell *sh)
{
	int	i;

	help_file(sh);
	i = 0;
	while (sh->manager.left_file[i])
		i++;
	sh->manager.left_file2 = malloc(sizeof(char *) * 3);
	if (!sh->manager.left_file2)
		return ;
	sh->manager.left_file2[0] = ft_strdup(sh->manager.left_file[0]);
	sh->manager.left_file2[1] = ft_strdup(sh->manager.left_file[i - 1]);
	sh->manager.left_file2[2] = NULL;
	sh->mat = sh->manager.left_file2;
}
