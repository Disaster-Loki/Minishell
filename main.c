/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:46:33 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:06:55 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_var(int value)
{
	static int	val;

	if (value == -1)
		return (val);
	else
		val = value;
	return (value);
}

void	ft_init_vars(t_shell *sh, char **env)
{
	(void)env;
	sh->i = 0;
	sh->pip = 0;
	sh->path = NULL;
	sh->flag_env = 0;
	sh->split = NULL;
	sh->temp_env = NULL;
	sh->env = dup_env(env);
	sh->status = get_var(-1);
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
		get_var2(1);
		shell.input = readline("MiniShell-> ");
		if (shell.input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			free_mat(shell.env);
			break ;
		}
		if (shell.input[0] != '\0')
			add_history(shell.input);
		read_line(&shell);
		free(shell.input);
	}
	return (0);
}
