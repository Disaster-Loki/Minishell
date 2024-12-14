/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:05:38 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_quotes(t_shell *sh, t_args *args, t_tokens *tok)
{
	char	*str;

	if (!ft_strchr(sh->input, '\'') && !ft_strchr(sh->input, '\"'))
		return (0);
	tok->st = tok->k;
	str = args[tok->j].str;
	while (str[tok->st] && str[tok->st] != '\'' && str[tok->st] != '\"')
		++tok->st;
	if (tok->st == (int)ft_strlen(str))
		return (0);
	if (!find_quotes(sh, str, &tok->st, &tok->en))
		return (0);
	args[tok->j].id = sh->in_q;
	return ((get_new_str(args, tok, str)), 1);
}

int	process_no_quotes(t_shell *sh, char *str, t_args *args, t_tokens *tok)
{
	int	x;
	int	end;

	x = tok->i;
	end = 0;
	tok->k = -1;
	while (str[tok->i] && str[tok->i] != ' ')
	{
		if (str[tok->i] == '\'' || str[tok->i] == '\"')
		{
			if (!handle_quotes(sh, str, tok, &end))
				return (0);
		}
		tok->i++;
	}
	args[tok->j].id = 32;
	args[tok->j].str = ft_strndup(str + x, tok->i - x);
	expansion(sh, args, tok);
	while (args[tok->j].str[++tok->k])
		process_quotes(sh, args, tok);
	not_redirect(sh, args, tok);
	(tok->j)++;
	return (1);
}

t_args	*tokenize(t_shell *sh, char *str)
{
	t_tokens	tok;
	t_args		*args;

	tok.i = 0;
	tok.j = 0;
	args = malloc(sizeof(t_args) * 1000);
	if (!args)
		return (NULL);
	while (str[tok.i])
	{
		tok.i = skip_spaces(str, tok.i);
		if (str[tok.i])
			process_no_quotes(sh, str, args, &tok);
	}
	args[tok.j].str = NULL;
	return (args);
}
