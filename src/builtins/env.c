/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:02:28 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/23 13:02:30 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmd_env(t_shell *sh)
{
	if (sh->mat[1])
	{
		printf("env: %s: No such file or directory\n", sh->mat[1]);
		return ;
	}
	print_matrix(sh->env);
}
