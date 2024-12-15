/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:04:01 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:05:35 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var2(int value)
{
	static int	val;

	if (value == -1)
		return (val);
	else
		val = value;
	return (value);
}

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		if (get_var2(-1) == 0)
			printf("\n");
		get_var(130);
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (get_var2(-1) == 1)
			rl_redisplay();
		get_var(130);
	}
	if (sig == SIGQUIT)
		rl_redisplay();
}

void	signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
