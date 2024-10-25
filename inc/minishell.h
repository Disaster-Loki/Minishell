/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:03:54 by sde-carv          #+#    #+#             */
/*   Updated: 2024/10/25 09:28:08 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
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

typedef struct s_shell
{
	char	*input;
	char	*path;
	char	*quotes;
	char	**mt;
	char	**env;
	char	**temp_env;
	char	**temp_unset;
}	t_shell;

void	cmd_pwd(void);
void	signals(void);
void	cmd_cd(t_shell *sh);
void	cmd_export(char **env);
void	cmd_unset(char ***env, char **to_remove);
void	cmd_exit(char **mt);
void	cmd_echo(char **mt);
void	free_mat(char **mt);
void	read_env(t_shell *sh);
int		get_path(t_shell *sh);
int		read_line(t_shell *sh);
int		matrix_line(char **mt);
int		read_line(t_shell *sh);
int		execut_cmd(t_shell *sh);
int		check_command(t_shell *sh);
void	print_matrix(char **matrix);
void	print_str_quotes(char *str);
char	*var_env(t_shell *sh, char *str);
void    cmd_export2(char ***env, char **mt);
char	**copy_mtx(char **env);
int		ft_strcmp(const char *s1, const char *s2);

#endif
