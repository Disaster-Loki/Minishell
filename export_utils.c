/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:07:52 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:07 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum_under(int k)
{
	return (ft_isdigit(k) || ft_isalpha(k) || k == '_');
}

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

int	valid_env_name(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
		return (0);
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum_under(str[i]))
			return (0);
	}
	if (ft_isdigit(str[0]))
		return (0);
	return (1);
}
