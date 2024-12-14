/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:56:48 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/14 11:05:42 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*equals_end(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
	{
		free(result);
		return (NULL);
	}
	i = -1;
	while (str[++i] != '=' && str[i])
		result[i] = str[i];
	result[i] = '\0';
	return (result);
}

int	found_equals2(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=' || str[i] == '\0')
			return (i);
	}
	return (i);
}

void	put_in_temp(t_shell *sh, char *to_remove)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (sh->env[++i])
	{
		if (ft_strncmp(sh->env[i], to_remove, found_equals2(sh->env[i])) != 0)
			sh->temp_unset[++j] = sh->env[i];
	}
	sh->temp_unset[j] = NULL;
	i = 0;
	while (sh->temp_unset[i])
		i++;
	sh->temp_unset2 = malloc(sizeof(char *) * (i + 1));
	if (!sh->temp_unset2)
		return ;
	i = -1;
	while (sh->temp_unset[++i])
		sh->temp_unset2[i] = ft_strdup(sh->temp_unset[i]);
	sh->temp_unset2[i] = NULL;
	free_mat(sh->env);
	sh->env = sh->temp_unset2;
}

void	rm_var(t_shell *sh, char *to_remove)
{
	int		i;
	char	*tmp;

	i = -1;
	while (sh->env[++i])
	{
		tmp = equals_end(sh->env[i]);
		if (ft_strcmp(tmp, to_remove) == 0)
		{
			free(tmp);
			put_in_temp(sh, to_remove);
			return ;
		}
		free(tmp);
	}
}

void	cmd_unset(t_shell *sh, char **to_remove)
{
	int		i;

	i = 1;
	if (to_remove[i] == NULL)
		return ;
	while (to_remove[i])
	{
		rm_var(sh, to_remove[i]);
		i++;
	}
}
