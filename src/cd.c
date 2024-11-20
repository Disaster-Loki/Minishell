/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:10:42 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/11/20 15:50:31 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char	cwd[PATH_MAX];
	char	*current_dir;

	current_dir = getcwd(cwd, sizeof(cwd));
	if (!current_dir)
		return (0);
	return (update_env_value(sh->env, key, current_dir));
}

void	cmd_cd(t_shell *sh)
{
	if (!sh->args[1].str)
		return (printf("cd: lack of arguments\n"), sh->status = 1, (void)0);
	if (sh->args[2].str)
	{
		printf("bash: cd: too many arguments\n");
		return (sh->status = 1, (void)0);
	}
	if (!chdir(sh->args[1].str))
	{
		if (!change_env(sh, "PWD"))
			printf("bash: cd: failed to update PWD\n");
		sh->status = 0;
	}
	else
	{
		printf("bash: cd: %s: No such file or directory\n", sh->args[1].str);
		sh->status = 1;
	}
}
