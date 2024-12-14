/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:05:20 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_of_redir(char **mt)
{
	int	i;

	i = -1;
	while (mt[++i])
	{
		if ((!ft_strncmp(mt[i], "<", 1) && ft_strlen(mt[i]) == 1)
			|| (!ft_strncmp(mt[i], "<<", 2) && ft_strlen(mt[i]) == 2))
			return (1);
	}
	return (0);
}

void	operators(t_shell *sh)
{
	sh->flag = 1;
	if (type_of_redir(sh->mat))
		exec_left(sh);
	else
		exec_right(sh);
}
