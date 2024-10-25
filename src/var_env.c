/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Variables_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:19:03 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/18 12:19:05 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*var_env(t_shell *sh, char *str)
{
	int		i;
	int		len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	i = -1;
	while (sh->env[++i])
		if (!ft_strncmp(sh->env[i], str, len) && sh->env[i][len] == '=')
			return (sh->env[i] + len + 1);
	return (NULL);
}

char	*var_name(char *str, int j)
{
	int		len;

	len = j;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (ft_substr(str, j, len - j));
}

char	*not_found(t_shell *sh, char *name, int *i)
{
	int		len;
	char	*sub;
	char	*exp;
	char	*rest;

	len = (int) ft_strlen(sh->input);
	sub = ft_substr(sh->input, 0, *i);
	rest = ft_substr(sh->input, *i + ft_strlen(name) + 1, len);
	exp = ft_strjoin(sub, rest);
	*i -= 1;
	free(sub);
	free(name);
	free(rest);
	return (exp);
}

char	*expand_var(t_shell *sh, int *i)
{
	char	*var;
	char	*sub;
	char	*rest;
	char	*name;
	char	*exp;

	name = var_name(sh->input, *i + 1);
	var = var_env(sh, name);
	if (!var)
		return (not_found(sh, name, i));
	sub = ft_substr(sh->input, 0, *i);
	rest = ft_substr(sh->input, *i + ft_strlen(name) + 1, ft_strlen(sh->input));
	exp = ft_strjoin(sub, var);
	exp = ft_strjoin(exp, rest);
	*i = 0;
	free(sub);
	free(rest);
	free(name);
	return (exp);
}

void	read_env(t_shell *sh)
{
	int		i;

	i = -1;
	while (sh->input[++i])
	{
		if (sh->input[i] == '$' && (sh->in_q == 0 || sh->in_q == 1))
		{
			if (sh->input[i + 1] == '\0')
				return ;
			sh->input = expand_var(sh, &i);
		}
	}
}
