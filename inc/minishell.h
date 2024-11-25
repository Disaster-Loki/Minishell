/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:45:16 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/21 17:53:22 by ptchipoc         ###   ########.fr       */
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
# include <linux/limits.h>
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
	int		len;
	char	*str;
	char	*temp;
}	t_args;

typedef struct s_shell
{
	char	***free_env;
	int		flag_env;
	int		i;
	int		in_q;
	char	**env;
	char	**mat;
	char	**temp_env;
	char	**env_free;
	char	**temp_unset;
	char	*free_quote;
	char	*tmp;
	char	*quotes;
	char	*path;
	t_args	*args;
	char	*input;
	int		status;
}	t_shell;

// Builtins
void	cmd_cd(t_shell *sh);
void	cmd_pwd(t_shell *sh);
void	cmd_env(t_shell *sh);
void	cmd_exit(t_shell *sh);
void	cmd_echo(t_shell *sh);

// Read Line
int		get_path(t_shell *sh);
int		read_line(t_shell *sh);
void	check_command(t_shell *sh);

// Expansions
void	expansion(t_shell *sh);
char	*get_name(char *str, int j);
char	*get_env(t_shell *sh, char *str);
char	*expand_var(t_shell *sh, int *i, int j);
int		states_cmd(t_shell *sh, int i, int j);
char	*not_found(t_shell *sh, char *name, int *i, int j);

// Tokenize
int		skip_spaces(char *str, int i);
t_args	*tokenize(t_shell *sh, char *str);
int		find_quotes(t_shell *sh, char *str, int *start, int *end);
int		process_quotes(t_shell *sh, t_args *args, int *i, int *j);
void	process_no_quotes(char *str, t_args *args, int *i, int *j);

// Signals
void	signals(void);
void	signal_handler(int sig);

// Utils
void	free_mat(char **mt);
int		matrix_line(char **mt);
void	print_matrix(char **matrix);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

// Exec_cmd
int		exec_cmd(t_shell *sh);
char	**ft_args(t_args *args);
void	signal_handler2(int sig);
void	child_process(char **split, t_shell *sh);

// Pipe
int		pipetting(t_shell *sh);
int		read_pipe(t_shell *sh);

// cmd_export.c
void	cmd_export(char **env);
int		found_equals(char *str);

//export_add..c
void	cmd_export2(t_shell *sh);

// export_utills.c
int		find_size(char *vari);
int		check_var(char *str);
int 	valid_env_name(char *str);
char	*delete_quote(t_shell *sh, char *str);

void	cmd_unset(t_shell *sh, char **to_remove);
void	free_array_mat(char ***array);
#endif
