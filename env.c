/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:02:28 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:33:45 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	print_env(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		if (have_equal(matrix[i]))
			printf("%s\n", matrix[i]);
	}
}

void	cmd_env(t_shell *sh)
{
	if (sh->mat[1])
	{
		xprint("env: ", sh->mat[1], 2);
		xprint(": No such file or directory\n", NULL, 2);
		sh->status = 127;
		return ;
	}
	if (!sh->path)
	{
		print_error(sh, "No such file or directory", 127);
		return ;
	}
	print_env(sh->env);
}
