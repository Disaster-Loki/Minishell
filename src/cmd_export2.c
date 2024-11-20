/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/19 13:47:03 by ptchipoc         ###   ########.fr       */
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

void	add_var1(char ***env, char *str, t_shell *sh)
{
	int		i;
	char	*dup;
	char	**free_temp;

	sh->flag = 0;
	i = 0;
	dup = ft_strdup(str);
	while ((*env)[i])
		i++;
	sh->temp_env = malloc(sizeof(char *) * (i + 2));
	if (!sh->temp_env)
		return ;
	i = -1;
	while ((*env)[++i])
		sh->temp_env[i] = (*env)[i];
	sh->temp_env[i++] = dup;
	sh->temp_env[i] = NULL;
	free_temp = *env;
	if (sh->flag == 1)
		free_mat(free_temp);
	sh->flag = 1;
	*env = sh->temp_env;
}

int	check_envi(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], str, find_size(env[i])) == 0) && (find_size(env[i]) == find_size(str)))
		{
		 	return (1);
		} 
		i++;
	}
	return (0);
}

void	ch_value(char ***env, char *str)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], str, find_size((*env)[i])) == 0 && found_equals(str))
		{
			(*env)[i] = ft_strdup(str);
			return ;
		}
		i++;
	}
}

void	cmd_export2(char ***env, char **mt, t_shell *sh)
{
	int	i;

	i = 1;
	while (mt[i])
	{
		if (check_envi(*env, mt[i]))
		{
			if (check_var(mt[i]))
				ch_value(env, delete_quote(mt[i]));
			else
				ch_value(env, mt[i]);
		}
		else
		{

			if (check_var(mt[i]))
				add_var1(env, delete_quote(mt[i]), sh);
			else
				add_var1(env, mt[i], sh);
		}
		i++;
	}
}
