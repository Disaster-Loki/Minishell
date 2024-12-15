/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:10:42 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/14 11:02:38 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_value(char **env, char *key, char *new_value)
{
	int		len;
	char	*tmp;

	len = ft_strlen(key);
	while (*env)
	{
		if (!ft_strncmp(*env, key, len) && (*env)[len] == '=')
		{
			tmp = *env;
			*env = ft_strjoin(key, "=");
			if (!*env)
				return (0);
			free(tmp);
			tmp = *env;
			*env = ft_strjoin(*env, new_value);
			if (!*env)
				return (0);
			free(tmp);
			return (1);
		}
		env++;
	}
	return (0);
}

int	change_env(t_shell *sh, char *key)
{
	char	*str;
	char	cwd[PATH_MAX];
	char	*current_dir;

	str = get_env(sh, "PWD");
	if (!str)
		return (0);
	current_dir = getcwd(cwd, sizeof(cwd));
	if (!current_dir)
		return (0);
	return (update_env_value(sh->env, key, current_dir));
}

int	add_env(t_shell *sh, char *str)
{
	if (str)
	{
		if (!valid_env_name(str))
			export_error(str);
		else if (check_envi(sh->env, str))
		{
			if (check_var(str))
				ch_value(sh->env, str);
			else
				ch_value(sh->env, str);
		}
		else
		{
			if (check_var(str))
				add_var(sh, str);
			else
				add_var(sh, str);
		}
		return (1);
	}
	return (0);
}

int	change_old(t_shell *sh, char *key)
{
	char	*str;
	char	*tmp;
	char	*join;

	str = ft_strdup(get_env(sh, "PWD"));
	if (!str)
		return (0);
	tmp = ft_strjoin(key, "=");
	join = ft_strjoin(tmp, str);
	add_env(sh, join);
	free(str);
	free(tmp);
	free(join);
	return (1);
}

void	cmd_cd(t_shell *sh)
{
	if (!sh->mat[1])
	{
		xprint("cd: lack of arguments\n", NULL, 2);
		return (sh->status = 1, (void)0);
	}
	if (sh->mat[2])
	{
		xprint("bash: cd: too many arguments\n", NULL, 2);
		return (sh->status = 1, (void)0);
	}
	if (!chdir(sh->mat[1]))
	{
		change_old(sh, "OLDPWD");
		if (!change_env(sh, "PWD"))
			xprint("bash: cd: failed to update PWD\n", NULL, 2);
		sh->status = 0;
	}
	else
	{
		xprint("bash: cd: ", sh->mat[1], 2);
		xprint(": ", strerror(errno), 2);
		xprint("\n", NULL, 2);
		sh->status = 1;
	}
}
