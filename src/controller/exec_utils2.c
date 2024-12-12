/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:12:21 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/12 13:12:25 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_abs(t_shell *sh)
{
	char	**arg;

	arg = sh->mat;
	if (execve(sh->args[0].str, arg, sh->env) == -1)
		handle_exec_error(sh->args[0].str, arg, sh);
	exit(127);
}

int	ft_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			status = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			status = 131;
		else
			status = 128 + WTERMSIG(status);
	}
	else
		status = WEXITSTATUS(status);
	return (status);
}

int	file_aux(t_shell *sh)
{
	if (sh->path == NULL)
	{
		xprint("bash", ": ", 2);
		xprint(sh->mat[0], ": No such file or directory\n", 2);
		return (-1);
	}
	if (!ft_strcmp(sh->mat[0], "bash") && sh->mat[1])
	{
		xprint("bash", ": ", 2);
		xprint(sh->mat[1], ": No such file or directory\n", 2);
		return (-1);
	}
	return (1);
}

int	file_dt_error(t_shell *sh)
{
	if (file_aux(sh) == -1)
		return (-1);
	if (sh->mat[0][0] == '/' && sh->mat[0][ft_strlen(sh->mat[0]) - 1] == '/')
	{
		xprint("bash", ": ", 2);
		xprint(sh->mat[0], ": Is a directory\n", 2);
		sh->status = 127;
		return (-1);
	}
	if (sh->mat[0][0] == '/')
	{
		xprint("bash", ": ", 2);
		xprint(sh->mat[0], ": No such file or directory\n", 2);
		sh->status = 127;
		return (-1);
	}
	return (1);
}
