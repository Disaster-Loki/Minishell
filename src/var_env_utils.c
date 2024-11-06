/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:12:32 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/06 14:12:34 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*var_env(t_shell *sh, char *str)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(str);
	while (sh->env[++i])
		if (!ft_strncmp(sh->env[i], str, len) && sh->env[i][len] == '=')
			return (sh->env[i] + len + 1);
	return (NULL);
}

int	states_cmd(t_shell *sh, int i)
{
	char	*st;
	char	*str;
	char	*exp;
	char	*rest;

	st = ft_itoa(sh->stat);
	str = ft_substr(sh->input, 0, i);
	rest = ft_substr(sh->input, i + 2, ft_strlen(sh->input));
	exp = ft_strjoin(str, st);
	exp = ft_strjoin(exp, rest);
	sh->input = exp;
	free(st);
	free(str);
	free(rest);
	return (1);
}