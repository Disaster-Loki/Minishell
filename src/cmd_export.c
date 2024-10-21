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
			if (env[i] > env[i + 1])
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				j = 1;
			}
		}
	}
	i = -1;
	while (env[++i])
		printf("declare -x %s\n", env[i]);
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
