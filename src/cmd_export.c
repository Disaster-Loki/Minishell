/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/24 13:08:00 by ptchipoc         ###   ########.fr       */
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

char    *equals_end(char *str)
{
    int i;
    char    *result;

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

void	put_in_temp(char ***env, char *current_env, char *to_remove)
{
	int	i;
	int j;
	t_shell	*handler;

	i = 0;
	(void)current_env;
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
	int i;

	i = 0;
    while ((*env)[i])
	{	
        if (ft_strcmp(equals_end((*env)[i]), to_remove) == 0)
		{
			put_in_temp(env, (*env)[i], to_remove);
			return ;
		}
		i++;
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
