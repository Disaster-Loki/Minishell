/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:29:25 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/07 16:29:29 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
}

void	signals2(void)
{
	signal(SIGINT, signal_handler);
}

int	execut_cmd(t_shell *sh)
{
	int		i;
	char	*str;
	char	**split;

	str = NULL;
	split = ft_split(sh->path, ':');
	if (fork() == 0)
	{
		i = -1;
		while (split[++i])
		{
			str = ft_strjoin(split[i], "/");
			str = ft_strjoin(str, sh->mt[0]);
			if (execve(str, sh->mt, sh->env) != -1)
			{
				free(str);
				free_mat(split);
			}
			free(str);
		}
		exit(0);
	}
	waitpid(-1, &sh->stat, 0);
	sh->stat = WEXITSTATUS(sh->stat);
	free_mat(split);
	return (1);
}