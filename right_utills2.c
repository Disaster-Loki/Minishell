/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_utills2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:44:20 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/14 11:05:32 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_get_file(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((!ft_strncmp(sh->mat[i], ">", 1) && ft_strlen(sh->mat[i]) == 1)
		|| (!ft_strncmp(sh->mat[i], ">>", 2)
			&& ft_strlen(sh->mat[i]) == 2))
	{
		while (sh->mat[i])
		{
			if ((!ft_strncmp(sh->mat[i], ">", 1)
					&& ft_strlen(sh->mat[i]) == 1)
				|| (!ft_strncmp(sh->mat[i], ">>", 2)
					&& ft_strlen(sh->mat[i]) == 2))
				sh->manager.file[j++] = ft_strdup(sh->mat[i + 1]);
			i++;
		}
		sh->manager.file[j] = NULL;
		return (0);
	}
	return (1);
}

int	help_get_dir(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((!ft_strncmp(sh->mat[i], ">", 1) && ft_strlen(sh->mat[i]) == 1)
		|| (!ft_strncmp(sh->mat[i], ">>", 2)
			&& ft_strlen(sh->mat[i]) == 2))
	{
		while (sh->mat[i])
		{
			if ((!ft_strncmp(sh->mat[i], ">", 1)
					&& ft_strlen(sh->mat[i]) == 1)
				|| (!ft_strncmp(sh->mat[i], ">>", 2)
					&& ft_strlen(sh->mat[i]) == 2))
				sh->manager.redir[j++] = ft_strdup(sh->mat[i]);
			i++;
		}
		sh->manager.redir[j] = NULL;
		return (0);
	}
	return (1);
}
