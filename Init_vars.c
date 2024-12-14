/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:29 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(char **mt, int *fd, int *len, int *i)
{
	*i = -1;
	*fd = -1;
	*len = matrix_line(mt);
}

int	initialize_split(t_split *spt, char *str)
{
	spt->str = str;
	spt->i = 0;
	spt->idx = 0;
	spt->res = malloc(sizeof(char *) * 1000);
	if (!spt->res)
		return (1);
	return (0);
}

int	handle_quotes2(t_shell *sh, t_split *spt, int *end)
{
	if (find_quotes(sh, spt->str, &spt->i, end))
	{
		spt->i = *end;
		return (0);
	}
	return (1);
}
