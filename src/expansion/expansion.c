/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:19 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/14 11:24:21 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_var(t_shell *sh, t_args *args, int *i, int j)
{
	char	*var;
	char	*sub;
	char	*rest;
	char	*name;
	char	*exp;

	name = get_name(args[j].str, *i + 1);
	var = get_env(sh, name);
	if (!var)
		return (not_found(args, name, i, j));
	args->len = ft_strlen(args[j].str);
	sub = ft_substr(args[j].str, 0, *i);
	rest = ft_substr(args[j].str, *i + ft_strlen(name) + 1, args->len);
	exp = ft_strjoin(sub, var);
	sh->tmp = exp;
	exp = ft_strjoin(sh->tmp, rest);
	*i = 0;
	free(sub);
	free(rest);
	free(name);
	free(sh->tmp);
	return (exp);
}

void	handle_expansion(t_shell *sh, t_args *args, t_tokens *tok, int *i)
{
	if (args[tok->j].str[*i] == '$')
	{
		args[tok->j].temp = args[tok->j].str;
		if (args[tok->j].str[*i + 1] == '?')
		{
			states_cmd(sh, args, *i, tok->j);
			return ;
		}
		if (args[tok->j].str[*i + 1] == ' '
			|| args[tok->j].str[*i + 1] == '\0')
			return ;
		args[tok->j].str = expand_var(sh, args, i, tok->j);
		free(args[tok->j].temp);
	}
}

void	expansion(t_shell *sh, t_args *args, t_tokens *tok)
{
	int	i;
	int	end;
	int	start;
	int	state;

	i = -1;
	end = 0;
	start = 0;
	state = 0;
	while (args[tok->j].str[++i])
	{
		is_in_quotes(&state, args[tok->j].str[i]);
		if (state == 1)
		{
			start = i;
			find_quotes(sh, args[tok->j].str, &start, &end);
			i = end;
		}
		handle_expansion(sh, args, tok, &i);
	}
}
