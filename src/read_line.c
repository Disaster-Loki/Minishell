/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:02:35 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/12 12:17:39 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	has_redir(char **mt)
{
	int	i;

	i = -1;
	while (mt[++i])
	{
		if ((!ft_strncmp(mt[i], "<", 1) && ft_strlen(mt[i]) == 1) || (!ft_strncmp(mt[i], "<<", 2) && ft_strlen(mt[i]) == 2) || (!ft_strncmp(mt[i], ">", 1) && ft_strlen(mt[i]) == 1) || (!ft_strncmp(mt[i], ">>", 2) && ft_strlen(mt[i]) == 2))
			return (1);
	}
	return (0);
}

int	check_command(t_shell *sh)
{
	sh->manager.control = 0;
	if (has_redir(sh->mt) && sh->redirect == 0)
		operators(sh);
	else if (!ft_strcmp(sh->mt[0], "export") && sh->mt[1] != NULL)
		cmd_export2(&sh->env, sh->mt);
	else if (!ft_strcmp(sh->mt[0], "export") && sh->mt[1] == NULL)
		cmd_export(sh->env);
	else if (!ft_strcmp(sh->mt[0], "echo"))
		cmd_echo(sh->mt);
	else if (!ft_strcmp(sh->mt[0], "unset"))
		cmd_unset(&sh->env, sh->mt);
	else if (!ft_strcmp(sh->mt[0], "pwd"))
		cmd_pwd();
	else if (!ft_strcmp(sh->mt[0], "env"))
		print_matrix(sh->env);
	else if (!ft_strcmp(sh->mt[0], "cd"))
		cmd_cd(sh);
	else if (!ft_strcmp(sh->mt[0], "exit"))
		cmd_exit(sh->mt);
	else if (!execut_cmd(sh))
		printf("Command '%s' not found\n", sh->mt[0]);
	return (1);
}

int	get_path(t_shell *sh)
{
	int		i;
	char	*path;

	i = -1;
	path = "PATH=";
	while (sh->env[++i])
	{
		if (!ft_strncmp(sh->env[i], path, 5))
		{
			sh->path = sh->env[i] + 5;
			return (1);
		}
	}
	return (0);
}

int	read_line(t_shell *sh)
{
	sh->redirect = 0;
	read_env(sh);
	sh->mt = ft_split(sh->input, ' ');
	if (!get_path(sh) || !check_command(sh))
		return (0);
	if (sh->manager.control == 0)
		free_mat(sh->mt);
	return (1);
}
