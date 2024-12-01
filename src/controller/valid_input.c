/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:46:33 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 17:53:33 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	handle_syntax_error(char *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 1);
	if (!token || token[0] == '\0')
		ft_putstr_fd("newline", 1);
	else
		ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	return (258);
}

int	check_syntax_error(t_shell *sh)
{
	int		i;
	char	*input;

	i = 0;
	input = sh->input;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (i == 0 || is_special_char(input[i + 1]))
				return (handle_syntax_error("|"));
		}
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i + 1] == '<' || input[i + 1] == '>')
				i++;
			if (input[i + 1] == '\0')
				return (handle_syntax_error("newline"));
			if (is_special_char(input[i + 1]))
				return (handle_syntax_error(input + i + 1));
		}
		i++;
	}
	return (0);
}

int	valid_quotes(t_shell *sh, char *str)
{
	int	i;
	int	end;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if(!find_quotes(sh, str, &i, &end))
				return (0);
			i = end;
		}
	}
	return (1);
}

int	validate_input(t_shell *sh)
{
	int	status;

	if (!valid_quotes(sh, sh->input))
	{
		sh->status = 2;
		return (-1);
	}
	status = check_syntax_error(sh);
	if (status == 258)
		sh->status = 1;
	return (status == 258);
}
