/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:46:33 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:06:06 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_characters(t_shell *sh, char *input, int *i, int *status)
{
	int	end;

	end = 0;
	if (input[*i] == '\'' || input[*i] == '\"')
	{
		if (!find_quotes(sh, input, i, &end))
			return (0);
		*i = end;
	}
	if (input[*i] == '|')
		*status = check_pipe_syntax(input, i);
	else if (input[*i] == '<' || input[*i] == '>')
		*status = check_redirect_syntax(input, i);
	else
		(*i)++;
	return (*status);
}

int	check_syntax_error(t_shell *sh)
{
	int		i;
	int		status;
	char	*input;

	i = 0;
	status = 0;
	input = sh->input;
	if (input[i] == '|')
		return (handle_syntax_error("|"));
	while (input[i])
	{
		status = syntax_characters(sh, input, &i, &status);
		if (status == 258)
			return (status);
	}
	return (0);
}

int	validate_input(t_shell *sh)
{
	int	status;

	if (!is_empty_input(sh->input))
	{
		sh->status = 0;
		return (-1);
	}
	if (!valid_quotes(sh, sh->input))
	{
		xprint("bash: ", "has quotes\n", 2);
		sh->status = 2;
		return (-1);
	}
	status = check_syntax_error(sh);
	if (status == 258)
		sh->status = 1;
	return (status == 258);
}
