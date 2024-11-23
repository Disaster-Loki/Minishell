/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:16:40 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/23 12:16:42 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	args_len(t_args *args)
{
	int	i;

	i = 0;
	while (args[i].str)
		i++;
	return (i);
}

int	exit_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	logout(t_shell *sh, int status)
{
	int	i;

	i = -1;
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	free(sh->input);
	if (sh->flag_env == 1)
		free_array_mat(sh->free_env);
	free_mat(sh->env);
	exit(status);
}

void	cmd_exit(t_shell *sh)
{
	int	num;

	num = 0;
	printf("exit\n");
	if (args_len(sh->args) > 2)
	{
		printf("bash: exit: too many arguments\n");
		sh->status = 1;
		return ;
	}
	if (sh->args[1].str && !exit_digit(sh->args[1].str))
	{
		printf("bash: exit: %s: numeric argument required\n", sh->args[1].str);
		logout(sh, 255);
	}
	if (sh->args[1].str)
		num = ft_atoi(sh->args[1].str);
	logout(sh, num % 256);
}
