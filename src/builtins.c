/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:06:03 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 18:18:38 by ptchipoc         ###   ########.fr       */
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

void free_array_mat(char ***array)
{
    int i;

    if (!array || !*array)
        return;

    i = 0;
    while ((*array)[i])
    {
        free((*array)[i]);
        i++;
    }
    free(*array);
    *array = NULL;
}

void	cmd_exit(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	free(sh->input);
	if (sh->flag_env == 1)
		free_array_mat(sh->free_env);
	printf("exit\n");
	free_mat(sh->env);
	sh->status = 0;
	exit(0);
}
