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

char	*expand_var(t_shell *sh, int *i, int j)
{
	char	*var;
	char	*sub;
	char	*rest;
	char	*name;
	char	*exp;

	name = get_name(sh->args[j].str, *i + 1);
	var = get_env(sh, name);
	if (!var)
		return (not_found(sh, name, i, j));
	sh->args->len = ft_strlen(sh->args[j].str);
	sub = ft_substr(sh->args[j].str, 0, *i);
	rest = ft_substr(sh->args[j].str, *i + ft_strlen(name) + 1, sh->args->len);
	exp = ft_strjoin(sub, var);
	sh->tmp = exp;
	exp = ft_strjoin(sh->tmp, rest);
	*i = 0;
	free(sub);
	free(rest);
	free(name);
	free(sh->tmp);
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
				sh->args[j].temp = sh->args[j].str;
				if (sh->args[j].str[i + 1] == '?')
				{
					states_cmd(sh, i, j);
					return ;
				}
				if (sh->args[j].str[i + 1] == ' '
					|| sh->args[j].str[i + 1] == '\0')
					return ;
				sh->args[j].str = expand_var(sh, &i, j);
			}
		}
	}
}
