/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/14 11:43:22 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int	find_quotes(t_shell *sh, char *str, int *start, int *end)
{
	int	i;

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

int	process_quotes(t_shell *sh, t_args *args, int *i, int *j)
{
	int		end;
	int		start;
	char	*str;

	start = *i;
	str = sh->input;
	sh->in_q = str[*i];
	if (find_quotes(sh, str, &start, &end))
	{
		if (sh->in_q == '\"')
			args[*j].id = 34;
		else if (sh->in_q == '\'')
			args[*j].id = 39;
		args[*j].str = ft_strndup(str + start + 1, end - start - 1);
		*i = end + 1;
	}
	else
	{
		args[*j].id = 73;
		args[*j].str = ft_strndup(str + start + 1, ft_strlen(str) - start - 1);
		*i = ft_strlen(str);
	}
	(*j)++;
	return (1);
}

void	process_no_quotes(char *str, t_args *args, int *i, int *j)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\"' && str[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	args[*j].id = 32;
	args[*j].str = ft_strndup(str + start, len);
	(*j)++;
}

t_args	*tokenize(t_shell *sh, char *str)
{
	int		i;
	int		j;
	t_args	*args;

	i = 0;
	j = 0;
	args = malloc(sizeof(t_args) * 7000);
	if (!args)
		return (NULL);
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (str[i] == '\"' || str[i] == '\'')
			process_quotes(sh, args, &i, &j);
		else if (str[i])
			process_no_quotes(str, args, &i, &j);
	}
	args[j].str = NULL;
	return (args);
}
