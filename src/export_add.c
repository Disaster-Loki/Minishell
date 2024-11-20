/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/20 15:41:38 by ptchipoc         ###   ########.fr       */
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

void	add_var1(t_shell *sh, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	sh->temp_env = malloc(sizeof(char *) * (matrix_line(sh->env) + 2));
	if (!sh->temp_env)
		return ;
	i = -1;
	while (sh->env[++i])
		sh->temp_env[i] = ft_strdup(sh->env[i]);
	sh->temp_env[i++] = ft_strdup(str);
	sh->temp_env[i] = NULL;
	tmp = sh->env;
	sh->env = sh->temp_env;
	free_mat(tmp);
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

void	ch_value(char **env, char *str)
{
	int	i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, find_size(env[i])) && found_equals(str))
		{
			tmp = env[i];
			env[i] = ft_strdup(str);
			free(tmp);
			return ;
		}
	}
}

void	cmd_export2(t_shell *sh)
{
	int	i;

	i = 1;
	(void)sh;
	while (sh->mat[i])
	{
		if (check_envi(sh->env, sh->mat[i]))
		{
			if (check_var(sh->mat[i]))
				ch_value(sh->env, delete_quote(sh, sh->mat[i]));
			else
				ch_value(sh->env, sh->mat[i]);
		}
		else
		{

			if (check_var(sh->mat[i]))
				add_var1(sh, delete_quote(sh, sh->mat[i]));
			else
				add_var1(sh, sh->mat[i]);
		}
		i++;
	}
}
