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

#include "../inc/minishell.h"

void	cmd_echo(t_args *args)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (args[i].str && !ft_strcmp(args[i].str, "-n"))
	{
		flag = 1;
		i++;
	}
	if (args[i].str == NULL)
	{
		if (!flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (args[i].str)
	{
		ft_putstr_fd(args[i].str, 1);
		if (args[i + 1].str)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
