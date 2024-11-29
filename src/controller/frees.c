/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:48:53 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/20 15:48:36 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_args(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->args[i].str)
		free(sh->args[i++].str);
	free(sh->args);
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

void	free_array_mat(char ***array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
