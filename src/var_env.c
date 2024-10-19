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
	char	*name;

	len = j;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	name = ft_substr(str, j, len - j);
	return (name);
}

char	*expand_var(t_shell *sh, int i)
{
	char	*var;
	char	*exp;
	char	*sub;
	char	*name;

	(void)sub;
	(void)exp;
	name = var_name(sh->input, i + 1);
	var = var_env(sh, name);
	if (!var)
	{
		//free(name);
		return (name);
	}

	/*sub = ft_substr(str, *j + ft_strlen(name) + 1, ft_strlen(str));
	printf("%s\n", sub);
	exp = ft_strjoin(var, sub);
	printf("%s\n", exp);
	while (exp[*j] && exp[*j] != '$')
		(*j)++;
	if (exp[*j] == '$')
		(*j)--;
	printf("%d\n", *j);
	free(name);
	free(sub);
	free(str);*/
	return (var);
}

void	read_env(t_shell *sh)
{
	int		i;

	i = -1;
	while (sh->input[++i])
	{
		if (sh->input[i] == '$')
			sh->input = expand_var(sh, i);
	}
}
