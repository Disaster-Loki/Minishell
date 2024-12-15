/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/15 20:34:52 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	helo_help_write(char **print, int *i, int *j, int *flag)
{
	while (print[*i][++(*j)])
	{
		if ((print[*i][*j] == '=' || print[*i][*j + 1] == '\0')
			&& found_equals(print[*i]))
		{
			printf("%c", print[*i][*j]);
			if (*flag == 0 || print[*i][*j + 1] == '\0')
				printf("\"");
			*flag = 1;
			if (print[*i][*j] == '=' && print[*i][*j + 1] == '\0')
				printf("\"");
		}
		else
			printf("%c", print[*i][*j]);
	}
}

void	help_write(char **print, int *i, int *j, int *flag)
{
	while (print[++(*i)])
	{
		printf("declare -x ");
		*j = -1;
		*flag = 0;
		if (end_with_equals(print[*i]))
			print_equals_end(print[*i]);
		else
			helo_help_write(print, i, j, flag);
		printf("\n");
	}
}

void	write_export(char **print)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = -1;
	help_write(print, &i, &j, &flag);
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
