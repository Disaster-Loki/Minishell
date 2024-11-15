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

#include "../inc/minishell.h"

char	*get_name(char *str, int j)
{
	int		len;

	len = j;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (ft_substr(str, j, len - j));
}

char	*get_env(t_shell *sh, char *str)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(str);
	while (sh->env[++i])
		if (!ft_strncmp(sh->env[i], str, len) && sh->env[i][len] == '=')
			return (sh->env[i] + len + 1);
	return (NULL);
}

/*int	states_cmd(t_shell *sh, int i)
{
	char	*st;
	char	*str;
	char	*exp;
	char	*rest;

	st = ft_itoa(sh->stat);
	str = ft_substr(sh->input, 0, i);
	rest = ft_substr(sh->input, i + 2, ft_strlen(sh->input));
	exp = ft_strjoin(str, st);
	exp = ft_strjoin(exp, rest);
	sh->input = exp;
	free(st);
	free(str);
	free(rest);
	return (1);
}*/

char	*not_found(t_shell *sh, char *name, int *i, int j)
{
	int		len;
	char	*sub;
	char	*exp;
	char	*rest;

	len = ft_strlen(sh->args[j].str);
	sub = ft_substr(sh->args[j].str, 0, *i);
	rest = ft_substr(sh->args[j].str, *i + ft_strlen(name) + 1, len);
	exp = ft_strjoin(sub, rest);
	*i = 0;
	free(sub);
	free(name);
	free(rest);
	free(sh->args[j].temp);
	return (exp);
}

char	*expand_var(t_shell *sh, int *i, int j)
{
	char	*var;
	char	*sub;
	char	*rest;
	char	*name;
	char	*exp;
	char	*tmp;

	name = get_name(sh->args[j].str, *i + 1);
	var = get_env(sh, name);
	if (!var)
		return (not_found(sh, name, i, j));
	sub = ft_substr(sh->args[j].str, 0, *i);
	rest = ft_substr(sh->args[j].str, *i + ft_strlen(name) + 1, ft_strlen(sh->args[j].str));
	exp = ft_strjoin(sub, var);
	tmp = exp;
	exp = ft_strjoin(tmp, rest);
	free(tmp);
	*i = 0;
	free(sub);
	free(rest);
	free(name);
	free(sh->args[j].temp);
	return (exp);
}

void	expansion(t_shell *sh)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (sh->args[++j].str)
	{
		i = -1;
		while (sh->args[j].str[++i])
		{
			if (sh->args[j].str[i] == '$' && sh->args[j].id != 39)
			{
				if (sh->args[j].str[i + 1] == '?')
				{
					//states_cmd(sh, i);
					return ;
				}
				if (sh->args[j].str[i + 1] == ' ' || sh->args[j].str[i + 1] == '\0')
					return ;
				sh->args[j].temp = sh->args[j].str;
				sh->args[j].str = expand_var(sh, &i, j);
			}
		}
	}
}