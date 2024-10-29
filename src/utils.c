/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:49:24 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/28 13:05:40 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		printf("%s\n", matrix[i]);
}

void	print_str_quotes(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '"')
			j++;
		ft_putchar_fd(str[j], 1);
		j++;
	}
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

void	free_mat2(char ***mt)
{
	int	i;
	
	if (mt)
	{
		i = -1;
		while ((*mt)[++i])
			free((*mt)[i]);
		free(*mt);
		*mt = NULL;
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

int	matrix_line(char **mt)
{
	int	len;

	len = 0;
	while (mt[len])
		len++;
	return (len);
}
