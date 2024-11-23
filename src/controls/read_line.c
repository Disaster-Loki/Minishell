/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 18:17:53 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_path(t_shell *sh)
{
	sh->path = get_env(sh, "PATH");
	if (sh->path == NULL)
		return (0);
	return (1);
}

void	check_command(t_shell *sh)
{
	if (sh->args[0].str)
	{
		if (!ft_strcmp(sh->args[0].str, "export") && !sh->args[1].str)
			cmd_export(sh->env);
		else if (!ft_strcmp(sh->args[0].str, "export") && sh->args[1].str)
			cmd_export2(sh);
		else if (!ft_strcmp(sh->args[0].str, "unset"))
			cmd_unset(sh, sh->mat);
		else if (!ft_strcmp(sh->args[0].str, "echo"))
			cmd_echo(sh);
		else if (!ft_strcmp(sh->args[0].str, "pwd"))
			cmd_pwd(sh);
		else if (!ft_strcmp(sh->args[0].str, "env"))
			cmd_env(sh);
		else if (!ft_strcmp(sh->args[0].str, "cd"))
			cmd_cd(sh);
		else if (!ft_strcmp(sh->args[0].str, "exit"))
			cmd_exit(sh);
		else if (!exec_cmd(sh))
			printf("%s: command not found\n", sh->args[0].str);
	}
}

int	read_line(t_shell *sh)
{
	int	i;

	i = -1;
	get_path(sh);
	sh->mat = ft_split(sh->input, ' ');
	// if (pipetting(sh))
	// 	return (0);
	sh->args = tokenize(sh, sh->input);
	expansion(sh);
	check_command(sh);
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	free_mat(sh->mat);
	return (0);
}
