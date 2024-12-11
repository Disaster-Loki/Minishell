/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/11 11:08:26 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_envi(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], str, find_size(env[i])) == 0)
			&& (find_size(env[i]) == find_size(str)))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	ch_value(char **env, char *str)
{
	int		i;
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

void	add_var(t_shell *sh, char *str)
{
	int		i;
	int		len;

	i = 0;
	len = matrix_line(sh->env);
	sh->temp_env = malloc(sizeof(char *) * (len + 2));
	if (!sh->temp_env)
		return ;
	i = -1;
	while (sh->env[++i])
		sh->temp_env[i] = ft_strdup(sh->env[i]);
	sh->temp_env[i++] = ft_strdup(str);
	sh->temp_env[i] = NULL;
	sh->free_env[sh->i++] = sh->env;
	sh->env = sh->temp_env;
	sh->flag_env = 1;
}

void	cmd_export2(t_shell *sh)
{
	int	i;

	i = 1;
	while (sh->mat[i])
	{
		if (!valid_env_name(sh->mat[i]))
			printf("bash: export: `%s': not a valid identifier\n", sh->mat[i]);
		else if (check_envi(sh->env, sh->mat[i]))
		{
			if (check_var(sh->mat[i]))
				ch_value(sh->env, sh->mat[i]);
			else
				ch_value(sh->env, sh->mat[i]);
		}
		else
		{
			if (check_var(sh->mat[i]))
				add_var(sh, sh->mat[i]);
			else
				add_var(sh, sh->mat[i]);
		}
		i++;
	}
}
