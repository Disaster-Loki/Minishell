/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comd_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/17 10:53:07 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**copy_mtx(char **env)
{
	char	**copy;
	int	i;

	i = 0;
	while (env[i])
		i++;
	copy = malloc(sizeof(char **) * (i + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (env[++i])
		copy[i] = env[i];
	copy[i] = NULL;
	return (copy);
}

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

void	cmd_export(char **env)
{
	int		i;
	int		j;
	char	*temp;
	char	**copy;

	j = 1;
	copy = copy_mtx(env);
	while (j)
	{
		i = -1;
		j = 0;
		while (copy[++i + 1])
		{
			if (compare(copy[i], copy[i + 1]) == 1)
			{
				temp = copy[i];
				copy[i] = copy[i + 1];
				copy[i + 1] = temp;
				j = 1;
			}
		}
	}
	i = -1;
	while (copy[++i])
		printf("declare -x %s\n", copy[i]);
}

void	cmd_unset(char **env, char **to_remove)
{
	int		i;
	int		j;
	char	**temp;

	temp = env;
	i = 0;
	
	if (to_remove[1] == NULL)
		return ;
	while (to_remove[++i])
	{
		j = -1;
		while (temp[++j])
		{
			if (!ft_strncmp(to_remove[i], temp[j], ft_strlen(to_remove[i]))
				&& temp[j][ft_strlen(to_remove[i])] == '=')
			{
				while (temp[j + 1])
				{
					env[j] = temp[j + 1];
					j++;
				}
				env[j] = NULL;
				break ;
			}
		}
	}
}
