/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:56:48 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/11/20 15:56:52 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*equals_end(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (str[++i] != '=' && str[i])
		result[i] = str[i];
	result[i] = '\0';
	return (result);
}

void	put_in_temp(char ***env, char *to_remove)
{
	int		i;
	int		j;
	t_shell	*handler;

	i = 0;
	handler = malloc(sizeof(t_shell));
	if (!handler)
		return ;
	while ((*env)[i])
		i++;
	handler->temp_unset = malloc(sizeof(char *) * (i + 1));
	if (!handler->temp_unset)
		return ;
	i = -1;
	j = -1;
	while ((*env)[++i])
	{	
		if (ft_strcmp(equals_end((*env)[i]), to_remove) != 0)
			handler->temp_unset[++j] = (*env)[i];
	}
	handler->temp_unset[j] = NULL;
	*env = handler->temp_unset;
}

void	rm_var(char ***env, char *to_remove)
{
	int	i;

	i = -1;
	while ((*env)[++i])
	{	
		if (ft_strcmp(equals_end((*env)[i]), to_remove) == 0)
		{
			put_in_temp(env, to_remove);
			return ;
		}
	}
}

void	cmd_unset(char ***env, char **to_remove)
{
	int		i;

	i = 1;
	if (to_remove[i] == NULL)
		return ;
	while (to_remove[i])
	{
		rm_var(env, to_remove[i]);
		i++;
	}
}
