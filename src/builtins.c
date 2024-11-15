/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:06:03 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/15 13:06:05 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
}

void	cmd_exit(t_shell *sh)
{
	int	i;

	i = -1;
	while (sh->args[++i].str)
		free(sh->args[i].str);
	free(sh->args);
	free(sh->input);
	printf("exit\n");
	exit(0);
}

void	cmd_cd(t_shell *sh)
{
	char	*home;

	if (sh->args[1].str == NULL)
	{
		home = get_env(sh, "HOME");
		if (home)
			chdir(home);
		return ;
	}
	if (sh->args[2].str)
	{
		printf("bash: cd: too many arguments\n");
		return ;
	}
	if (chdir(sh->args[1].str) != 0)
		printf("bash: cd: %s: No such file or directory\n", sh->args[1].str);
}

void	cmd_echo(t_args *args)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (args[i].str && !ft_strncmp(args[i].str, "-n", ft_strlen(args[i].str)))
	{
		flag = 1;
		i++;
	}
	if (args[i].str == NULL)
	{
		if (!flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (args[i].str)
	{
		ft_putstr_fd(args[i].str, 1);
		if (args[i + 1].str)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}