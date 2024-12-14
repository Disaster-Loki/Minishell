/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:56 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

char	*get_rest(char *str, int end)
{
	char	*rest;

	if (end + 1 < (int)ft_strlen(str))
		rest = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
	else
		rest = ft_strdup("");
	return (rest);
}

int	handle_quotes(t_shell *sh, char *str, t_tokens *tok, int *end)
{
	int	start;

	start = tok->i;
	if (find_quotes(sh, str, &start, end))
	{
		tok->i = *end;
		return (1);
	}
	return (0);
}

int	find_quotes(t_shell *sh, char *str, int *start, int *end)
{
	int		i;

	i = *start;
	sh->in_q = str[i++];
	while (str[i] && str[i] != sh->in_q)
		i++;
	if (str[i] == sh->in_q)
	{
		*end = i;
		return (1);
	}
	return (0);
}

void	get_new_str(t_args *args, t_tokens *tok, char *str)
{
	char	*exp;

	tok->sub = ft_substr(str, 0, tok->st);
	tok->join = ft_substr(str, tok->st + 1, tok->en - tok->st - 1);
	tok->rest = get_rest(str, tok->en);
	exp = ft_strjoin(tok->sub, tok->join);
	args[tok->j].str = ft_strjoin(exp, tok->rest);
	tok->k = tok->st + (int)ft_strlen(tok->join) - 1;
	free(str);
	free(tok->sub);
	free(tok->join);
	free(tok->rest);
	free(exp);
}
