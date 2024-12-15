/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:46:33 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/15 17:36:38 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	herepipe(t_shell *sh, int *i)
{
	char	*line;
	int		status;
	char	*new_input;

	(void)status;
	line = readline("> ");
	if (!line)
	{
		xprint("bash: syntax error: unexpected end of file\n", NULL, 2);
		xprint("exit\n", NULL, 2);
		return (0);
	}
	new_input = ft_strjoin(sh->input, line);
	free(sh->input);
	sh->input = new_input;
	*i = 0;
	free(line);
	return (1);
}

int	syntax_characters(t_shell *sh, char *input, int *i)
{
	if (input[*i] == '|')
		return (check_pipe_syntax(sh, input, i));
	if (input[*i] == '>' || input[*i] == '<')
		return (check_redirect_syntax(input, i));
	return (0);
}

int	check_syntax_error(t_shell *sh)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (sh->input[i] == ' ')
		i++;
	if (sh->input[i] == '|')
		return (handle_syntax_error("|"));
	while (sh->input[i])
	{
		status = syntax_characters(sh, sh->input, &i);
		if (status == 258)
			return (258);
		i++;
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
