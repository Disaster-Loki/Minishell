/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:02:35 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/17 09:02:38 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_command(char **mt)
{
	if (!ft_strncmp(mt[0], "echo", 4))
		cmd_echo(mt);
	else if (!ft_strncmp(mt[0], "pwd", 3))
		cmd_pwd();
	else
		printf("Command '%s' not found\n", mt[0]);
	return (1);
}

int	read_line(char *input, char **env)
{
	(void)env;
	char	**split;

	split = ft_split(input, ' ');
	if (!check_command(split))
		return (0);
	return (1);
}

