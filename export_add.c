/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/14 11:04:03 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**free_temp;

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
	free_temp = sh->env;
	sh->env = sh->temp_env;
	free_mat(free_temp);
	sh->flag_env = 1;
}

void	export_error(char *str)
{
	xprint("bash: export: `", str, 2);
	xprint("': not a valid identifier\n", "", 2);
}

void	cmd_export2(t_shell *sh)
{
	int	i;

	i = 1;
	while (sh->mat[i])
	{
		if (!valid_env_name(sh->mat[i]))
			export_error(sh->mat[i]);
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
