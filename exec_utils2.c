/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:12:21 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 12:11:49 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (WTERMSIG(status) == SIGQUIT)
		{
			printf("Quit (core dumped)\n");
			status = 131;
		}
		else
			status = 128 + WTERMSIG(status);
	}
	else
		status = WEXITSTATUS(status);
	return (status);
}

int	print_error(t_shell *sh, char *message, int status)
{
	xprint("bash: ", NULL, 2);
	xprint(sh->mat[0], NULL, 2);
	xprint(": ", message, 2);
	if (errno)
		xprint(strerror(errno), NULL, 2);
	xprint("\n", NULL, 2);
	sh->status = status;
	return (-1);
}

int	file_dt_error(t_shell *sh)
{
	if (!sh->path)
		return (print_error(sh, "No such file or directory", 127));
	if (!ft_strcmp(sh->mat[0], "bash") && sh->mat[1])
		return (print_error(sh, "No such file or directory", 127));
	if (sh->mat[0][0] == '/' && sh->mat[0][ft_strlen(sh->mat[0]) - 1] == '/')
		return (print_error(sh, "Is a directory", 127));
	if (sh->mat[0][0] == '/')
		return (print_error(sh, "No such file or directory", 127));
	return (1);
}
