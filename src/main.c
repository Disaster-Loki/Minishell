/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:08:26 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/16 12:08:28 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int av, char **args, char *env[])
{
	t_shell	shell;

	(void)av;
	(void)args;
	shell.env = env;
	while (1)
	{
		signals();
		shell.input = readline(BOLD_GREEN"MiniShell->  "RESET);
		if (shell.input == NULL)
		{
			printf("exit\n");
			break ;
		}
		add_history(shell.input);
		read_line(&shell);
		free(shell.input);
	}
	return (0);
}
