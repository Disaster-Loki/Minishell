/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:09 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/15 17:40:10 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	s_quotes(int c)
{
	return (c == '\'' || c == '\"');
}

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	check_pipe_syntax(t_shell *sh, char *input, int *i)
{
	int	pipe_count;

	pipe_count = 1;
	(*i)++;
	while (input[*i] == '|')
	{
		pipe_count++;
		(*i)++;
	}
	while (input[*i] == ' ')
		(*i)++;
	if (pipe_count > 1 || input[*i] == '|')
		return (handle_syntax_error("|"));
	if (input[*i] == '\0')
	{
		if (herepipe(sh, i))
			return (0);
		return (258);
	}
	return (0);
}

int	check_redirect_syntax(char *input, int *i)
{
	int		count;
	char	redirect;

	count = 1;
	redirect = input[*i];
	(*i)++;
	while (input[*i] == redirect)
	{
		count++;
		(*i)++;
	}
	if (count > 2 || (input[*i] == '<' || input[*i] == '>'))
		return (handle_syntax_error(input + (*i) - count));
	while (input[*i] == ' ')
		(*i)++;
	if (input[*i] == '\0' || input[*i] == '|'
		|| input[*i] == '<' || input[*i] == '>')
		return (handle_syntax_error(input + *i));
	return (0);
}
