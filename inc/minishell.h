/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-carv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:03:54 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/16 12:03:56 by sde-carv         ###   ########.fr       */
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
}	t_args;

typedef struct s_shell
{
	int		in_q;
	int		fd_in;
	int		stat;
	char	**mt;
	char	*path;
	char	**env;
	char	*input;
	t_args	*args;
}	t_shell;

int		skip_spaces(char *str, int i);
int		find_quotes(t_shell *sh, char *str, int *start, int *end);
int		process_quotes(t_shell *sh, char *str, t_args *args, int *i, int *j);
void	process_no_quotes(char *str, t_args *args, int *i, int *j);
t_args	*ft_alter_split(t_shell *sh, char *str);
char	*ft_strndup(const char *s, size_t n);
void	signal_handler(int sig);
int		states_cmd(t_shell *sh, int i);
int		read_pipe(t_shell *sh);
void	cmd_pwd(void);
void	signals(void);
void	cmd_cd(t_shell *sh);
void	cmd_exit(char **mt);
void	cmd_echo(char **mt);
void	free_mat(char **mt);
int		get_path(t_shell *sh);
void	read_env(t_shell *sh);
int		read_line(t_shell *sh);
int		matrix_line(char **mt);
int		read_line(t_shell *sh);
int		execut_cmd(t_shell *sh);
int		check_command(t_shell *sh);
void	print_matrix(char **matrix);
void	print_str_quotes(char *str);
char	*var_env(t_shell *sh, char *str);
int		ft_strcmp(const char *s1, const char *s2);

#endif
