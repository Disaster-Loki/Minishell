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

void	ft_init_vars(t_shell *sh, char **env)
{
	(void)env;
	sh->i = 0;
	sh->status = 0;
	sh->path = NULL;
	sh->flag_env = 0;
	sh->split = NULL;
	sh->temp_env = NULL;
	sh->env = ft_env(env);
	//sh->free_env = malloc(sizeof(char **) * 1024);
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
