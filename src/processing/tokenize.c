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

int process_quotes(t_shell *sh, t_args *args, int *k, int *j) {
    int		end;
	int		start;
    char	*str;
    char	*sub;
	char	*join;
	char	*rest;
	char	*exp;

	start = 0;
	str = args[*j].str;
	while (str[start] && str[start] != '\'' && str[start] != '\"')
		start++;
	if (start == (int) ft_strlen(str))
		return (0);
	if (find_quotes(sh, str, &start, &end))
	{
		
		printf("Inicio K = %d\n", *k);
		printf("Inicio str = %s\n", str);
		sub = ft_substr(str, 0, start);
		printf("sub = %s\n", sub);
		join = ft_substr(str, start + 1, end - start - 1);
		printf("join = %s\n", join);
		rest = ft_substr(str, end + 1, ft_strlen(str) - end - 1);
		printf("rest = %s\n", rest);
		exp = ft_strjoin(sub, join);
		printf("exp = %s\n", exp);
		args[*j].id = sh->in_q;
		args[*j].str = ft_strjoin(exp, rest);
		printf("args.str = %s\n", args[*j].str);
		*k = (int)(ft_strlen(exp));
		printf("k = %d\n", *k);
		free(str);
		free(sub);
		free(join);
		free(rest);
		free(exp);
	}
    return (1);
}

void	process_no_quotes(t_shell *sh, char *str, t_args *args, int *i, int *j)
{
	int	k;
	int	len;
	int	start;

	k = -1;
	len = 0;
	start = *i;
	while (str[*i] && str[*i] != ' ')
	{
		len++;
		(*i)++;
	}
	args[*j].id = 32;
	args[*j].str = ft_strndup(str + start, len);
	while (args[*j].str[++k])
		process_quotes(sh, args, &k, j);
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
		process_no_quotes(sh, str, args, &i, &j);
	}
	args[j].str = NULL;
	return (args);
}
