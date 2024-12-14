/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:09 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:06:02 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	check_pipe_syntax(char *input, int *i)
{
	if (*i == 0 || is_special_char(input[*i + 1]))
		return (handle_syntax_error("|"));
	(*i)++;
	while (input[*i] == ' ')
		(*i)++;
	if (input[*i] == '\0' || is_special_char(input[*i]))
		return (handle_syntax_error("|"));
	return (0);
}

int	check_redirect_syntax(char *input, int *i)
{
	char	current;

	current = input[*i];
	(*i)++;
	if (input[*i] == current)
		(*i)++;
	while (input[*i] == ' ')
		(*i)++;
	if (input[*i] == '\0' || is_special_char(input[*i]))
		return (handle_syntax_error(input + *i));
	return (0);
}
