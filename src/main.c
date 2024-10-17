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
	(void)av;
	(void)args;
	char	*input;

	while (1)
	{
		signals();
		input = readline(BOLD_GREEN"MiniShell->  "RESET);
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		read_line(input, env);
		free(input);
	}
	return (0);
}