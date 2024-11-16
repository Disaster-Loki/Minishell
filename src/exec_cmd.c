/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:09 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/15 15:37:12 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_handler2(int sig)
{
	(void)sig;
	printf("\n");
}

char	**ft_args(t_args *args)
{
	int		i;
	int		size;
	char	**arg;

	i = -1;
	size = 0;
	while (args[size].str)
		size++;
	arg = malloc(sizeof(char *) * (size + 1));
	while (args[++i].str)
		arg[i] = ft_strdup(args[i].str);
	arg[i] = NULL;
	return (arg);
}

void	child_process(char **split, t_shell *sh)
{
	int		i;
	char	*str;
	char	*tmp;
	char	**arg;

	i = -1;
	arg = ft_args(sh->args);
	while (split[++i])
	{
		str = ft_strjoin(split[i], "/");
		tmp = str;
		str = ft_strjoin(str, sh->args[0].str);
		if (execve(str, arg, sh->env) != -1)
		{
			free(str);
			free(tmp);
			free_mat(arg);
			free_mat(split);
			exit(0);
		}
		free(tmp);
		free(str);
	}
	exit(1);
}

int	exec_cmd(t_shell *sh)
{
	char	**split;

	split = ft_split(sh->path, ':');
	if (!split)
		return (0);
	if (fork() == 0)
		child_process(split, sh);
	signal(SIGINT, signal_handler2);
	waitpid(-1, &sh->status, 0);
	sh->status = WEXITSTATUS(sh->status);
	if (sh->status == 1)
		return (free_mat(split), 0);
	return (free_mat(split), 1);
}
