/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:39:05 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	val_rdir(t_args *args, int i)
{
	if (args[i].id == 34 || args[i].id == 39)
		return (0);
	return (1);
}

int	has_redir(t_shell *sh, char **mt)
{
	int	i;

	i = -1;
	while (mt[++i])
	{
		if (val_rdir(sh->args, i) && ((!ft_strncmp(mt[i], ">", 1)
					&& ft_strlen(mt[i]) == 1) || (!ft_strncmp(mt[i], ">>", 2)
					&& ft_strlen(mt[i]) == 2) || (!ft_strncmp(mt[i], "<", 1)
					&& ft_strlen(mt[i]) == 1) |(!ft_strncmp(mt[i], "<<", 2)
					&& ft_strlen(mt[i]) == 2)))
			return (1);
	}
	return (0);
}
