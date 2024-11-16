/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/14 11:24:21 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_path(t_shell *sh)
{
	sh->path = get_env(sh, "PATH");
	if (sh->path == NULL)
		return (0);
	return (1);
}

int	check_command(t_shell *sh)
{
	if (!ft_strcmp(sh->args[0].str, "echo"))
		cmd_echo(sh->args);
	else if (!ft_strcmp(sh->args[0].str, "pwd"))
		cmd_pwd(sh);
	else if (!ft_strcmp(sh->args[0].str, "env"))
		print_matrix(sh->env);
	else if (!ft_strcmp(sh->args[0].str, "cd"))
		cmd_cd(sh);
	else if (!ft_strcmp(sh->args[0].str, "exit"))
		cmd_exit(sh);
	else if (!exec_cmd(sh))
		printf("%s: command not found\n", sh->args[0].str);
	return (1);
}

//printf("Id: %d\nSTR: %s\n", sh->args[i].id, sh->args[i].str);
int	read_line(t_shell *sh)
{
	int	i;

	i = -1;
	get_path(sh);
	if (pipetting(sh))
		return (0);
	sh->args = tokenize(sh, sh->input);
	expansion(sh);
	check_command(sh);
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	return (0);
}
