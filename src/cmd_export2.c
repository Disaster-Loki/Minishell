/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/25 10:00:30 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_until_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	printf("%c", str[i]);
	printf("\"\"");
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

char	*delete_quote(char *str)
{
	int		i;
	int		j;
	t_shell	*handler;

	handler = malloc(sizeof(t_shell));
	if (!handler)
		return (0);
	handler->quotes = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!handler->quotes)
		return (0);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != '"')
		{
			handler->quotes[j] = str[i];
			j++;
		}
	}
	handler->quotes[j] = '\0';
	return (handler->quotes);
}

void	add_var1(char ***env, char *str)
{
	int		i;
	char	*dup;
	t_shell	*hundler;

	hundler = malloc(sizeof(t_shell));
	i = 0;
	dup = ft_strdup(str);
	while ((*env)[i])
		i++;
	hundler->temp_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while ((*env)[++i])
		hundler->temp_env[i] = (*env)[i];
	hundler->temp_env[i] = dup;
	i++;
	hundler->temp_env[i] = NULL;
	*env = hundler->temp_env;
	free(hundler);
}

void	cmd_export2(char ***env, char **mt)
{
	int	i;

	i = 1;
	while (mt[i])
	{
		if (check_var(mt[i]))
			add_var1(env, delete_quote(mt[i]));
		else
			add_var1(env, mt[i]);
		i++;
	}
}
