/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 15:03:22 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_redir(char **mt)
{
	int	i;

	i = -1;
	while (mt[++i])
	{
		if ((!ft_strncmp(mt[i], ">", 1) && ft_strlen(mt[i]) == 1) || (!ft_strncmp(mt[i], ">>", 2) && ft_strlen(mt[i]) == 2))
			return (1);
	}
	return (0);
}