/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:56:34 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/11/20 10:56:38 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_n_option(t_args *args, int *i)
{
	int	k;

	k = 0;
	if (args[*i].str[0] == '-')
	{
		while (args[*i].str[++k])
		{
			if (args[*i].str[k] != 'n')
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
	if (sh->args[i].str && is_n_option(sh->args, &i))
		flag = 1;
	if (sh->args[i].str == NULL)
	{
		if (!flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (sh->args[i].str)
	{
		ft_putstr_fd(sh->args[i].str, 1);
		if (sh->args[i + 1].str)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	sh->status = 0;
}
