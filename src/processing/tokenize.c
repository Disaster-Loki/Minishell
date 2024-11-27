/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 15:03:22 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int process_quotes(t_shell *sh, t_args *args, int *k, int *j) {
    int  end;
    int  start;
    char *str;
    char *sub;
    char *join;
    char *rest;
    char *exp;

    start = *k;
    str = args[*j].str;
    while (str[start] && str[start] != '\'' && str[start] != '\"')
        start++;
    if (start == (int)ft_strlen(str))
        return (0);
    if (find_quotes(sh, str, &start, &end))
    {
        sub = ft_substr(str, 0, start);
        join = ft_substr(str, start + 1, end - start - 1);
        if (end + 1 < (int)ft_strlen(str))
            rest = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
        else
            rest = ft_strdup("");
        exp = ft_strjoin(sub, join);
		args[*j].id = sh->in_q;
        args[*j].str = ft_strjoin(exp, rest);
        *k = start + (int)ft_strlen(join) - 1;
        free(str);
        free(sub);
        free(join);
        free(rest);
        free(exp);
    }
    return (1);
}

int	process_no_quotes(t_shell *sh, char *str, t_args *args, int *i, int *j)
{
	int	k;
	int	x;
	int	end;
	int	start;

	k = -1;
	x = *i;
	end = 0;
	start = 0;
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			start = *i;
			if (find_quotes(sh, str, &start, &end))
				*i = end;
			else
				return (0);
		}
		(*i)++;
	}
	args[*j].id = 32;
	args[*j].str = ft_strndup(str + x, *i - x);
	while (args[*j].str[++k])
		process_quotes(sh, args, &k, j);
	(*j)++;
	return (1);
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
		process_no_quotes(sh, str, args, &i, &j);
	}
	args[j].str = NULL;
	return (args);
}
