/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:43:17 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:24 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str, int j)
{
	int		len;

	len = j;
	while (str[len] && !s_quotes(str[len])
		&& (ft_isalnum(str[len]) || str[len] == '_'))
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
