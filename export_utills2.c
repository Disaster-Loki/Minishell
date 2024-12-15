/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utills2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:34:56 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/15 20:35:11 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_equals(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

int	end_with_equals(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '=' && str[i + 1] == '\0')
		return (1);
	return (0);
}

void	print_equals_end(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		printf("%c", str[i]);
		if (str[i] == '=' && flag == 0)
		{
			printf("\"");
			flag = 1;
		}
	}
	if (flag == 1)
		printf("\"");
}
