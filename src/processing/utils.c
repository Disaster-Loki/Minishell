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

int	skip_spaces(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	find_quotes(t_shell *sh, char *str, int *start, int *end)
{
	int	i;

	i = *start;
	sh->in_q = str[i++];
	while (str[i] && str[i] != sh->in_q)
		i++;
	if (str[i] == sh->in_q)
	{
		*end = i;
		return (1);
	}
	return (0);
}


