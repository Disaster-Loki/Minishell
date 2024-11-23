/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:02:00 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/16 16:02:03 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	states_cmd(t_shell *sh, int i, int j)
{
	char	*n;
	char	*str;
	char	*exp;
	char	*rest;
	char	*tmp;

	n = ft_itoa(sh->status);
	str = ft_substr(sh->args[j].str, 0, i);
	rest = ft_substr(sh->args[j].str, i + 2, ft_strlen(sh->args[j].str));
	exp = ft_strjoin(str, n);
	tmp = exp;
	exp = ft_strjoin(exp, rest);
	sh->args[j].str = exp;
	free(n);
	free(str);
	free(tmp);
	free(rest);
	free(sh->args[j].temp);
	return (1);
}

char	*not_found(t_shell *sh, char *name, int *i, int j)
{
	int		len;
	char	*sub;
	char	*exp;
	char	*rest;

	len = ft_strlen(sh->args[j].str);
	sub = ft_substr(sh->args[j].str, 0, *i);
	rest = ft_substr(sh->args[j].str, *i + ft_strlen(name) + 1, len);
	exp = ft_strjoin(sub, rest);
	*i = 0;
	free(sub);
	free(name);
	free(rest);
	free(sh->args[j].temp);
	return (exp);
}
