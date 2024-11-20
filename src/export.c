/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/20 12:24:24 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] < s2[i])
		return (0);
	return (1);
}

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

void	write_export(char **print)
{
	int	i;
	int	j;

	i = -1;
	while (print[++i])
	{
		printf("declare -x ");
		j = -1;
		while (print[i][++j])
		{
			if ((print[i][j] == '=' || print[i][j + 1] == '\0')
				&& found_equals(print[i]))
			{	
				printf("%c\"", print[i][j]);
				if (print[i][j] == '=' && print[i][j + 1] == '\0')
					printf("\"");
			}
			else
				printf("%c", print[i][j]);
		}
		printf("\n");
	}
}

void	cmd_export(char **env)
{
	int		i;
	int		j;
	char	*temp;

	j = 1;
	while (j)
	{
		i = -1;
		j = 0;
		while (env[++i + 1])
		{
			if (compare(env[i], env[i + 1]))
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				j = 1;
			}
		}
	}
	write_export(env);
}
