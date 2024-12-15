/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_utills2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:03:45 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 16:08:39 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str)
{
	if ((!ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		|| (!ft_strncmp(str, "<<", 1)
			&& ft_strlen(str) == 2))
		return (1);
	return (0);
}

int	is_word(char *str)
{
	if (is_redir(str))
		return (0);
	return (1);
}

int	flag_to_status2(t_shell *sh)
{
	int	i;
	int	flag;

	flag = 0;
	i = 3;
	if (!sh->mat[i])
		return (1);
	if (sh->mat[i] && !sh->mat[i + 1])
		return (0);
	while (sh->mat[i++])
	{
		if (is_word(sh->mat[i]))
		{
			if (flag == 1)
				return (0);
			flag = 1;
		}
		else if (is_redir(sh->mat[i]))
		{
			if (flag == 2)
				return (0);
			flag = 2;
		}
	}
	return (1);
}

int	verify_status2(t_shell *sh)
{
	int	i;
	int	flag;

	i = 2;
	flag = 0;
	while (sh->mat[i])
	{
		if (is_word(sh->mat[i]))
		{
			if (flag == 1)
				return (0);
			flag = 1;
		}
		else if (is_redir(sh->mat[i]))
		{
			if (flag == 2)
				return (0);
			flag = 2;
		}
		i++;
	}
	return (1);
}

int	verify_status(t_shell *sh)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (sh->mat[++i])
	{
		if (is_word(sh->mat[i]))
		{
			if (flag == 1)
				return (0);
			flag = 1;
		}
		else if (is_redir(sh->mat[i]))
		{
			if (flag == 2)
				return (0);
			flag = 2;
		}
	}
	return (1);
}
