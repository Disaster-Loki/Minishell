/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_utills.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:07:52 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/11/21 12:26:22 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_size(char *vari)
{
	int	i;

	i = 0;
	while (vari[i] != '=' && vari[i] != '\0')
		i++;
	return (i);
}

int	check_var(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
			return (1);
	}
	return (0);
}

char	*delete_quote(t_shell *sh, char *str)
{
	int		i;
	int		j;
	int		ch;

	sh->quotes = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!sh->quotes)
		return (0);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			ch = str[i];
		if (str[i] != ch)
		{
			sh->quotes[j] = str[i];
			j++;
		}
	}
	sh->quotes[j] = '\0';
	return (sh->quotes);
}
