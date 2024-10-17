/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:53:05 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/17 10:53:07 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
}

void	cmd_exit(char **mt)
{
	free_mat(mt);
	printf("exit\n");
	exit(0);
}

void	cmd_cd(char **mt)
{
	
}	

void	cmd_echo(char **mt)
{
	int	i;

	i = 1;
	if (mt[i] && !ft_strncmp(mt[i], "-n", ft_strlen(mt[i])))
		i++;
	if (mt[i] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	while (mt[i])
	{
		print_str_quotes(mt[i]);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (mt[1] && !ft_strncmp(mt[1], "-n", ft_strlen(mt[1])))
		return ;
	ft_putchar_fd('\n', 1);
}
