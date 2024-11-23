/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:48:53 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/20 15:48:36 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		printf("%s\n", matrix[i]);
}

int	matrix_line(char **mt)
{
	int	len;

	len = 0;
	while (mt[len])
		len++;
	return (len);
}

void	free_mat(char **mt)
{
	int	i;

	if (mt)
	{
		i = -1;
		while (mt[++i])
			free(mt[i]);
		free(mt);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void free_array_mat(char ***array)
{
    int i;

    if (!array || !*array)
        return;

    i = 0;
    while ((*array)[i])
    {
        free((*array)[i]);
        i++;
    }
    free(*array);
    *array = NULL;
}
