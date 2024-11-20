/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:46:33 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/19 13:48:12 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**copy_mtx(char **env)
{
	int		i;
	t_shell	*handler;
	char	*copy[1024];
	char	**copy2;

	handler = malloc(sizeof(t_shell));
	i = 0;
	while (env[i])
		i++;
	copy2 = malloc(sizeof(char *) * (i + 1));
	if (!copy2)
		return (NULL);
	i = -1;
	while (env[++i])
		copy[i] = env[i];
	i = -1;
	while (copy[++i])
		copy2[i] = copy[i];
	copy[i] = NULL;
	free(handler);
	return (copy2);
}

int	main(int av, char **args, char **env)
{
	t_shell	shell;

	(void)av;
	(void)args;
	shell.temp_env = NULL;
	shell.env = env;
	shell.status = 0;
	shell.flag = 0;
	while (1)
	{
		signals();
		shell.input = readline(BOLD_GREEN"MiniShell-> "RESET);
		if (shell.input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		add_history(shell.input);
		read_line(&shell);
		free(shell.input);
	}
	return (0);
}
