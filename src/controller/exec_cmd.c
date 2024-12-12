/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:09 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/12 13:29:01 by ptchipoc         ###   ########.fr       */
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

void	child_process(t_shell *sh)
{
	int		i;
	char	*tmp;
	char	**arg;

	signal(SIGQUIT, SIG_DFL);
	i = -1;
	arg = sh->mat;
	sh->split = ft_split(sh->path, ':');
	if (arg[0][0] == '.' && arg[0][1] == '/')
		exec_abs(sh);
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

int	handle_child_process(t_shell *sh, pid_t pid)
{
	signal(SIGINT, signal_handler2);
	signal(SIGQUIT, signal_handler2);
	waitpid(pid, &sh->status, 0);
	sh->status = ft_status(sh->status);
	if (sh->status == 127)
		return (0);
	return (1);
}

int	file_dt_error(t_shell *sh)
{
	if (sh->path == NULL)
	{
		xprint(sh->mat[0], ": No such file or directory\n", 2);
		return (-1);
	}
	if (!ft_strcmp(sh->mat[0], "bash") && sh->mat[1])
	{
		xprint(sh->mat[1], ": No such file or directory\n", 2);
		return (-1);
	}
	/*if (access(sh->mat[0], F_OK) != 0)
	{
		xprint("bash", ": ", 2);
        xprint(sh->mat[0], ": No such file or directory\n", 2);
        sh->status = 127;
    }*/
	return (1);
}

int	exec_cmd(t_shell *sh)
{
	pid_t	pid;
	char	*str;

	str = ft_substr(sh->mat[0], 0, ft_strlen("/bin/"));
	if (!ft_strcmp(str, "/bin/"))
	{
		pid = fork();
		if (pid == 0)
			exec_abs(sh);
		free(str);
		return (handle_child_process(sh, pid));
	}
	free(str);
	if (file_dt_error(sh) == -1)
		return (-1);
	if (!ft_strcmp(sh->mat[0], ""))
		return (0);
	pid = fork();
	if (pid == 0)
		child_process(sh);
	return (handle_child_process(sh, pid));
}
