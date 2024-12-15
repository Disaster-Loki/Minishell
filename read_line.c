/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:15:34 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xprint(char *str, char *str2, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd(str2, fd);
}

void	check_command(t_shell *sh)
{
	if (sh->mat[0])
	{
		if (has_redir(sh, sh->mat) && sh->redirect == 0)
			operators(sh);
		else if (!ft_strcmp(sh->mat[0], "export") && !sh->mat[1])
			cmd_export(sh->env);
		else if (!ft_strcmp(sh->mat[0], "export") && sh->mat[1])
			cmd_export2(sh);
		else if (!ft_strcmp(sh->mat[0], "unset"))
			cmd_unset(sh, sh->mat);
		else if (!ft_strcmp(sh->mat[0], "echo"))
			cmd_echo(sh);
		else if (!ft_strcmp(sh->mat[0], "pwd"))
			cmd_pwd(sh);
		else if (!ft_strcmp(sh->mat[0], "env"))
			cmd_env(sh);
		else if (!ft_strcmp(sh->mat[0], "cd"))
			cmd_cd(sh);
		else if (!ft_strcmp(sh->mat[0], "exit"))
			cmd_exit(sh);
		else if (!exec_cmd(sh))
		{
			xprint(sh->mat[0], ": command not found\n", 2);
		}
	}
}

int	read_line(t_shell *sh)
{
	sh->redirect = 0;
	sh->path = get_env(sh, "PATH");
	if (validate_input(sh))
		return (-1);
	if (ft_alter_strchr(sh, sh->input, '|') && pipetting(sh))
		return (0);
	if (alter_redirects(sh) == -1)
		return (-1);
	sh->args = tokenize(sh, sh->input);
	sh->mat = ft_args(sh->args);
	check_command(sh);
	if (sh->args[0].str)
		free_args(sh);
	return (0);
}
