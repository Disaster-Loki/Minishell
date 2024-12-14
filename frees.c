/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:48:53 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:14 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->args[i].str)
		free(sh->args[i++].str);
	free(sh->args);
	if (sh->mat)
		free_mat(sh->mat);
}

void	free_mat(char **mt)
{
	int	i;

	if (mt)
	{
		i = -1;
		while (mt[++i])
			free(mt[i]);
		free(mt);
	}
}

void	handle_exec_error(char *tmp, char **arg, t_shell *sh)
{
	if (errno == EACCES)
	{
		if (tmp)
			free(tmp);
		free_mat(arg);
		free_mat(sh->split);
		exit(126);
	}
}
