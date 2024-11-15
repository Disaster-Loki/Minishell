/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:45:16 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/14 10:45:21 by sde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/inc/libft.h"

# define RESET "\033[0m"
# define GREEN "\033[0;32m"
# define BOLD_GREEN "\033[1;32m"
# define COOL_EMOJI "😎"

typedef struct s_args
{
	int		id;
	char	*str;
	char	*temp;
}	t_args;

typedef struct s_shell
{
	int		in_q;
	char	**env;
	char	**mat;
	char	*path;
	t_args	*args;
	char	*input;
	int		status;
}	t_shell;

// Builtins
void	cmd_pwd(void);
void	cmd_exit(t_shell *sh);
void	cmd_cd(t_shell *sh);
void	cmd_echo(t_args *args);

void	free_mat(char **mt);
int		exec_cmd(t_shell *sh);
void	print_matrix(char **matrix);
int		ft_strcmp(const char *s1, const char *s2);
int		get_path(t_shell *sh);
char	*get_env(t_shell *sh, char *str);
void	signals(void);
void	expansion(t_shell *sh);
int		read_line(t_shell *sh);
void	signal_handler(int sig);
t_args	*tokenize(t_shell *sh, char *str);
char	*ft_strndup(const char *s, size_t n);

#endif