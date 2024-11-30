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

#include "../../inc/minishell.h"

void	child_process(t_shell *sh)
{
	int		i;
	char	*tmp;
	char	**arg;

	i = -1;
	arg = sh->mat;
	sh->split = ft_strjoin_alt(sh->split, "/");
	while (sh->split[++i])
	{
		tmp = sh->split[i];
		sh->split[i] = ft_strjoin(sh->split[i], sh->args[0].str);
		if (execve(sh->split[i], arg, sh->env) == -1)
			handle_exec_error(tmp, arg, sh);
		free(tmp);
		free(sh->split[i]);
	}
	free(sh->split);
	exit(127);
}

int	handle_child_process(t_shell *sh, pid_t pid)
{
	signal(SIGINT, signal_handler2);
	waitpid(pid, &sh->status, 0);
	if (WIFSIGNALED(sh->status))
	{
		if (WTERMSIG(sh->status) == SIGINT)
			sh->status = 130;
		else
			sh->status = 128 + WTERMSIG(sh->status);
	}
	else
		sh->status = WEXITSTATUS(sh->status);
	free_mat(sh->split);
	if (sh->status == 130 || sh->status == 126)
		return (-1);
	else if (sh->status == 127)
		return (0);
	return (1);
}

int	exec_cmd(t_shell *sh)
{
	pid_t pid;

	sh->split = ft_split(sh->path, ':');
	if (!sh->split)
		return (0);
	pid = fork();
	if (pid == 0)
		child_process(sh);
	return (handle_child_process(sh, pid));
}
