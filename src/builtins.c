/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:06:03 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/20 12:11:35 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_pwd(t_shell *sh)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		sh->status = 0;
	}
}

void	cmd_exit(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	free(sh->input);
	printf("exit\n");
	if (sh->flag == 1)
		free_mat(sh->temp_env);
	free_mat(sh->env);
	exit(0);
}