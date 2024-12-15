/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:09 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:03:33 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		sh->split[i] = ft_strjoin(sh->split[i], sh->mat[0]);
		if (execve(sh->split[i], arg, sh->env) == -1)
			handle_exec_error(tmp, arg, sh);
		free(tmp);
		free(sh->split[i]);
	}
	free_args(sh);
	free(sh->split);
	exit(127);
}

int	handle_child_process(t_shell *sh, pid_t pid)
{
	signal(SIGINT, signal_handler);
	waitpid(pid, &sh->status, 0);
	sh->status = ft_status(sh->status);
	if (sh->status == 127)
		return (0);
	return (1);
}

int	exec_cmd(t_shell *sh)
{
	pid_t	pid;
	char	*str;

	str = ft_substr(sh->mat[0], 0, ft_strlen("/bin/"));
	if (!ft_strcmp(str, "/bin/")
		&& sh->mat[0][ft_strlen("/bin/")] != '\0')
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
	get_var2(0);
	pid = fork();
	if (pid == 0)
		child_process(sh);
	return (handle_child_process(sh, pid));
}
