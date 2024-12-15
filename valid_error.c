/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:28:36 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 15:28:41 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_empty_input(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
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
			if (!find_quotes(sh, str, &i, &end))
				return (0);
			i = end;
		}
	}
	return (1);
}
