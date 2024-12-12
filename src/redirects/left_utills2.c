/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_utills2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:03:45 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/12 08:04:51 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redir(char *str)
{
	if (!ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		return (1);
	return (0);
}

int	is_word(char *str)
{
	if (is_redir(str))
		return (0);
	return (1);
}

int	verify_status(t_shell *sh)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (sh->mat[++i])
	{
		if (is_word(sh->mat[i]))
		{
			if (flag == 1)
				return (0);
			flag = 1;
		}
		else if (is_redir(sh->mat[i]))
		{
			if (flag == 2)
				return (0);
			flag = 2;
		}
	}
	return (1);
}
