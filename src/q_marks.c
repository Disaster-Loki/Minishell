/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:58:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/22 16:58:21 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	search_ch(char *str, char c, int i)
{
	while (str[i])
		if (str[i++] == c)
			return (1);
	return (0);
}

char	*mode_str(char *str, int i)
{
	char	*start;
	char	*mid;
	char	*rest;
	char	*exp;

	start = ft_substr(str, 0, i - 1);
	mid = ft_substr(str, 0, i - 1);
	rest = ft_substr(str, 0, i - 1);
	exp = ft_strjoin(start, mid);
	exp = ft_strjoin(exp, rest);
	return (exp);
}

void	quotation_marks(t_shell *sh, char *str)
{
	int	i;

	i = -1;
	sh->in_q = 0;
	while (str[++i])
	{
		if (str[i] == '\"' && sh->in_q != 2)
			sh->in_q = (sh->in_q == 1) ? 0 : 1;
		else if (str[i] == '\'' && sh->in_q != 1)
			sh->in_q = (sh->in_q == 2) ? 0 : 2;
	}
}
