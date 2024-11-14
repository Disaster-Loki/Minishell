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

int	read_line(t_shell *sh)
{
	sh->args = tokenize(sh, sh->input);
	expansion(sh);
	for(int i = 0; sh->args[i].str != NULL; i++)
		printf("Id: %d\nSTR: %s\n", sh->args[i].id, sh->args[i].str);
	free(sh->args);
	return (0);
}