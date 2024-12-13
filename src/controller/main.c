/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:46:33 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/13 17:24:59 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**dup_env(char **env)
{
	int		i;
	char	**res;

	i = matrix_line(env);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		res[i] = ft_strdup(env[i]);
	res[i] = NULL;
	return (res);
}

void	ft_init_vars(t_shell *sh, char **env)
{
	(void)env;
	sh->i = 0;
	sh->status = 0;
	sh->path = NULL;
	sh->flag_env = 0;
	sh->split = NULL;
	sh->temp_env = NULL;
	sh->env = dup_env(env);
	sh->free_env = malloc(sizeof(char **) * 1024);
}

int	main(int av, char **args, char **env)
{
	t_shell	shell;

	(void)av;
	(void)args;
	ft_init_vars(&shell, env);
	while (1)
	{
		signals();
		shell.input = readline("MiniShell-> ");
		if (shell.input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			free_mat(shell.env);
			break ;
		}
		if (is_empty_input(shell.input))
			add_history(shell.input);
		read_line(&shell);
		free(shell.input);
	}
	clear_history();
	return (0);
}
