/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_left_utills2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:43:43 by ptchipoc          #+#    #+#             */
/*   Updated: 2024/12/14 17:50:22 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_delldoble(t_shell *sh)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (sh->mat[++i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			j++;
	}
	sh->manager.dell_double = malloc(sizeof(char *) * (j + 1));
	if (!sh->manager.dell_double)
		return ;
	i = -1;
	j = 0;
	while (sh->mat[++i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			sh->manager.dell_double[j++] = ft_strdup(sh->mat[i + 1]);
	}
	sh->manager.dell_double[j] = NULL;
}

int	help_redir_first(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i += 2;
		else
		{
			j++;
			i++;
		}
	}
	sh->manager.arg_left = malloc(sizeof(char *) * (j + 1));
	if (!sh->manager.arg_left)
		return (0);
	return (1);
}

void	redir_first(t_shell *sh)
{
	int	i;
	int	j;

	if (!help_redir_first(sh))
		return ;
	i = 0;
	j = 0;
	while (sh->mat[i])
	{
		if (!ft_strncmp(sh->mat[i], "<<", 2) && ft_strlen(sh->mat[i]) == 2)
			i += 2;
		else
			sh->manager.arg_left[j++] = ft_strdup(sh->mat[i++]);
	}
	sh->manager.arg_left[j] = NULL;
	sh->mat = sh->manager.arg_left;
}

void	help_with_file(t_shell *sh)
{
	int		i;
	char	*temp;

	i = 0;
	put_in_delldoble(sh);
	while (sh->manager.dell_double[i])
	{
		while (1)
		{
			temp = readline("> ");
			if (!temp)
				return ;
			if (!ft_strncmp(sh->manager.dell_double[i],
					temp, ft_strlen(sh->manager.dell_double[i]))
				&& temp[ft_strlen(sh->manager.dell_double[i])] == '\0')
			{
				free(temp);
				break ;
			}
		}
		i++;
	}
	free_mat(sh->manager.dell_double);
}

void	with_file(t_shell *sh)
{
	int	pid;

	help_with_file(sh);
	redir_first(sh);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		check_command(sh);
		sh->redirect = 1;
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}
