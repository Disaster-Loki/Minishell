/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:09 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:03:49 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_alter_strchr(t_shell *sh, char *str, char c)
{
	int	i;
	int	end;
	int	start;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i;
			find_quotes(sh, str, &start, &end);
			i = end;
		}
	}
	return (0);
}
