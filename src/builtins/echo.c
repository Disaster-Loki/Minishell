/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:56:34 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/10 12:50:13 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_n_option(char **mat, int *i)
{
	int	k;

	k = 0;
	if (mat[*i][0] == '-')
	{
		while (mat[*i][++k])
		{
			if (mat[*i][k] != 'n')
				return (0);
		}
		(*i)++;
		return (1);
	}
	return (0);
}

void	cmd_echo(t_shell *sh)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (sh->mat[i] && is_n_option(sh->mat, &i))
		flag = 1;
	if (sh->mat[i] == NULL)
	{
		if (!flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (sh->mat[i])
	{
		ft_putstr_fd(sh->mat[i], 1);
		if (sh->mat[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	sh->status = 0;
}
