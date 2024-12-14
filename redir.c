/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:05:16 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_spaces_around(char *input, int start, int len)
{
	char	*sub;
	char	*redir;
	char	*rest;

	sub = ft_strndup(input, start);
	redir = ft_strndup(input + start, len);
	rest = ft_strdup(input + start + len);
	if (!sub || !redir || !rest)
		return (NULL);
	input = strjoin_and_free(sub, redir, rest);
	if (!input)
		return (NULL);
	return (input);
}

void	handle_double_redirect(t_shell *sh, t_redir *redir)
{
	char	*tmp;

	if ((redir->i == 0 || sh->input[redir->i - 1] != ' ')
		|| sh->input[redir->i + 2] != ' ')
	{
		tmp = sh->input;
		sh->input = add_spaces_around(sh->input, redir->i, 2);
		free(tmp);
	}
	redir->i += 2;
}

void	handle_single_redirect(t_shell *sh, t_redir *redir)
{
	char	*tmp;

	if ((redir->i == 0 || sh->input[redir->i - 1] != ' ')
		|| sh->input[redir->i + 1] != ' ')
	{
		tmp = sh->input;
		sh->input = add_spaces_around(sh->input, redir->i, 1);
		free(tmp);
	}
	redir->i += 1;
}

int	alter_redirects(t_shell *sh)
{
	t_redir	redir;

	redir.i = 0;
	while (sh->input[redir.i])
	{
		if (is_quotes(sh->input[redir.i]))
		{
			redir.start = redir.i;
			if (!handle_quotes3(sh, sh->input, &redir))
				return (-1);
		}
		if (is_redirection_operator(sh->input[redir.i]))
		{
			if (sh->input[redir.i + 1] == sh->input[redir.i])
				handle_double_redirect(sh, &redir);
			else
				handle_single_redirect(sh, &redir);
		}
		redir.i++;
	}
	return (1);
}
