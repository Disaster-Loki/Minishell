/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:46:33 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 17:53:33 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_env(char **env)
{
	int		i;
	int		rows;
	char	**res;

	i = -1;
	rows = matrix_line(env);
	res = malloc(sizeof(char *) * (rows + 1));
	if (!res)
		return (NULL);
	while (++i < rows)
		res[i] = ft_strdup(env[i]);
	res[i] = NULL;
	return (res);
}

int	main(int av, char **args, char **env)
{
	t_shell	shell;

	(void)av;
	(void)args;
	shell.temp_env = NULL;
	shell.env = ft_env(env);
	shell.status = 0;
	shell.free_env = malloc(sizeof(char **) * 1024);
	shell.i = 0;
	shell.flag_env = 0;
	while (1)
	{
		signals();
		shell.input = readline(BOLD_GREEN"MiniShell-> "RESET);
		if (shell.input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			free_mat(shell.env);
			break ;
		}
		add_history(shell.input);
		read_line(&shell);
		free(shell.input);
	}
	return (0);
}
