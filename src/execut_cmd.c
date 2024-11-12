/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:29:25 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/07 16:29:29 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_handler2(int sig)
{
	(void)sig;
	printf("\n");
}

static int	exec_cmd(char *cmd, char **args, char **env)
{
	if (execve(cmd, args, env) != -1)
		return (1);
	return (0);
}

static void	child_process(char **split, t_shell *sh)
{
	int		i;
	char	*str;

	i = -1;
	while (split[++i])
	{
		str = ft_strjoin(split[i], "/");
		str = ft_strjoin(str, sh->mt[0]);
		if (exec_cmd(str, sh->mt, sh->env))
		{
			free(str);
			free_mat(split);
			exit(0);
		}
		free(str);
	}
	exit(1);
}

int	execut_cmd(t_shell *sh)
{
	char	**split;

	split = ft_split(sh->path, ':');
	if (fork() == 0)
		child_process(split, sh);
	signal(SIGINT, signal_handler2);
	waitpid(-1, &sh->stat, 0);
	sh->stat = WEXITSTATUS(sh->stat);
	return (free_mat(split), 1);
}
