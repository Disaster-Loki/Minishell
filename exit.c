/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:16:40 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:07:46 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_limits(char *str)
{
	char		*endptr;
	long long	value;

	if (str == NULL || str[0] == '\0')
		return (0);
	value = ft_strtoll(str, &endptr, 10);
	if (*endptr != '\0')
		return (0);
	if (value < LLONG_MIN || value > LLONG_MAX)
		return (0);
	return (1);
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
	if (ft_limits(str) == 0)
		return (0);
	return (1);
}

void	logout(t_shell *sh, int status)
{
	int	i;

	i = -1;
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	if (sh->input)
		free(sh->input);
	if (sh->env)
		free_mat(sh->env);
	if (sh->mat)
		free_mat(sh->mat);
	exit(status);
}

void	cmd_exit(t_shell *sh)
{
	int	num;

	num = 0;
	printf("exit\n");
	if (sh->mat[1] && !exit_digit(sh->mat[1]))
	{
		printf("bash: exit: %s: numeric argument required\n", sh->mat[1]);
		logout(sh, 255);
	}
	if (matrix_line(sh->mat) > 2)
	{
		printf("bash: exit: too many arguments\n");
		sh->status = 1;
		return ;
	}
	if (sh->mat[1])
		num = ft_atoi(sh->mat[1]);
	logout(sh, num % 256);
}
