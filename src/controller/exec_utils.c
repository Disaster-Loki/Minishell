/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:09 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/15 15:37:12 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signal_handler2(int sig)
{
	(void)sig;
	printf("\n");
}

char	**ft_args(t_args *args)
{
	int		i;
	int		size;
	char	**arg;

	i = -1;
	size = 0;
	while (args[size].str)
		size++;
	arg = malloc(sizeof(char *) * (size + 1));
	while (args[++i].str)
		arg[i] = ft_strdup(args[i].str);
	arg[i] = NULL;
	return (arg);
}

char	**ft_strjoin_alt(char **spl, char *s)
{
	int		i;
	char	*tmp;

	i = -1;
	while (spl[++i])
	{
		tmp = spl[i];
		spl[i] = ft_strjoin(spl[i], s);
		free(tmp);
	}
	return (spl);
}
