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

int	is_in_quotes(int *state, char c)
{
	if (c == '\'' && *state == 0)
		*state = 1;
	else if (c == '\'' && *state == 1)
		*state = 0;
	else if (c == '"' && *state == 0)
		*state = 2;
	else if (c == '"' && *state == 2)
		*state = 0;
	return (*state);
}

int	states_cmd(t_shell *sh, t_args *args, int i, int j)
{
	char	*n;
	char	*str;
	char	*exp;
	char	*rest;
	char	*tmp;

	n = ft_itoa(sh->status);
	str = ft_substr(args[j].str, 0, i);
	rest = ft_substr(args[j].str, i + 2, ft_strlen(args[j].str));
	exp = ft_strjoin(str, n);
	tmp = exp;
	exp = ft_strjoin(exp, rest);
	args[j].str = exp;
	free(n);
	free(str);
	free(tmp);
	free(rest);
	free(args[j].temp);
	return (1);
}

char	*not_found(t_args *args, char *name, int *i, int j)
{
	int		len;
	char	*sub;
	char	*exp;
	char	*rest;

	len = ft_strlen(args[j].str);
	sub = ft_substr(args[j].str, 0, *i);
	rest = ft_substr(args[j].str, *i + ft_strlen(name) + 1, len);
	if (sub[0] == '\0' && rest[0] == '\0')
		exp = ft_strdup("");
	else
		exp = ft_strjoin(sub, rest);
	*i = 0;
	free(sub);
	free(name);
	free(rest);
	free(args[j].temp);
	return (exp);
}
