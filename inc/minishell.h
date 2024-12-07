/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:45:16 by sde-carv          #+#    #+#             */
/*   Updated: 2024/11/29 12:57:33 by ptchipoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <wait.h>
# include <errno.h>
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

typedef struct s_redir
{
	int		i;
	int		end;
	int		start;
}	t_redir;

typedef struct s_split
{
	int		i;
	int		idx;
	char	*str;
	char	**res;
}	t_split;

typedef struct s_args
{
	int		id;
	int		len;
	char	*str;
	char	*temp;
}	t_args;

typedef struct s_file
{
	int		fd;
	int		flag;
	char	**arg2;
	int		control;
	char	*arg[1024];
	char	*file[1024];
	char	*redir[1024];
}	t_file;

typedef struct s_tokens
{
	int		i;
	int		j;
	int		k;
	int		st;
	int		en;
	char	*sub;
	char	*join;
	char	*rest;
}	t_tokens;

typedef struct s_shell
{
	int		i;
	int		in_q;
	char	*tmp;
	int		rdir;
	t_args	*args;
	char	**env;
	char	**mat;
	char	**mat2;
	char	*path;
	char	*input;
	char	**split;
	int		status;
	char	*quotes;
	t_file	manager;
	int		flag_env;
	int		redirect;
	char	**temp_env;
	char	**env_free;
	char	*free_quote;
	char	***free_env;
	int		n_rdir[1000];
	char	**temp_unset;
}	t_shell;

int			ft_isspace(char c);
int			ft_get_digit(char c);
int			is_special_char(char c);
int			validate_input(t_shell *sh);
int			check_syntax_error(t_shell *sh);
int			handle_syntax_error(char *token);
int			check_pipe_syntax(char *input, int *i);
int			check_redirect_syntax(char *input, int *i);
int			ft_alter_strchr(t_shell *sh, char *str, char c);
long long	ft_strtoll(const char *str, char **endptr, int base);

// right_utills.c
void		get_dir(t_shell *sh);
void		get_arg(t_shell *sh);
void		get_file(t_shell *sh);

// Signals
void		signals(void);
void		signal_handler(int sig);
void		signal_handler2(int sig);

// Builtins
void		cmd_cd(t_shell *sh);
void		cmd_pwd(t_shell *sh);
void		cmd_env(t_shell *sh);
void		cmd_exit(t_shell *sh);
void		cmd_echo(t_shell *sh);

// Read Line
int			get_path(t_shell *sh);
int			read_line(t_shell *sh);
void		check_command(t_shell *sh);

// Export
int			check_var(char *str);
int			find_size(char *vari);
void		cmd_export(char **env);
int			found_equals(char *str);
void		cmd_export2(t_shell *sh);
int			valid_env_name(char *str);

// Utils
void		free_mat(char **mt);
int			matrix_line(char **mt);
void		print_matrix(char **matrix);
char		*ft_strndup(const char *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);

// Unset
void		operators(t_shell *sh);
void		free_args(t_shell *sh);
void		filter_tokens(char **mat);
void		free_array_mat(char ***array);
int			has_redir(char **mt, int *n_rdir);
void		cmd_unset(t_shell *sh, char **to_remove);

// Exec_cmd
int			exec_cmd(t_shell *sh);
char		**ft_args(t_args *args);
void		signal_handler2(int sig);
void		child_process(t_shell *sh);
char		**ft_strjoin_alt(char **spl, char *s);
int			handle_child_process(t_shell *sh, pid_t pid);
void		handle_exec_error(char *tmp, char **arg, t_shell *sh);

// Expansions
char		*get_name(char *str, int j);
int			is_in_quotes(int *state, char c);
char		*get_env(t_shell *sh, char *str);
int			states_cmd(t_shell *sh, t_args *args, int i, int j);
char		*not_found(t_args *args, char *name, int *i, int j);
void		expansion(t_shell *sh, t_args *args, t_tokens *tok);

// Pipeline
int			pipetting(t_shell *sh);
int			read_pipe(t_shell *sh);
char		*extract_token(t_split *spt, int start);
int			initialize_split(t_split *spt, char *str);
char		**full_split(t_shell *sh, char *str, char c);
void		init_vars(char **mt, int *fd, int *len, int *i);
int			handle_quotes2(t_shell *sh, t_split *spt, int *end);
int			process_segment(t_shell *sh, t_split *spt, char delt);

// Tokenize
int			is_quotes(char c);
int			alter_redirects(t_shell *sh);
int			skip_spaces(char *str, int i);
char		*get_rest(char *str, int end);
int			is_redirection_operator(char c);
t_args		*tokenize(t_shell *sh, char *str);
char		*ft_strcpy(char *dest, const char *src);
char		*strjoin_and_free(char *s1, char *s2, char *s3);
char		*add_spaces_around(char *input, int start, int len);
void		get_new_str(t_args *args, t_tokens *tok, char *str);
void		handle_single_redirect(t_shell *sh, t_redir *redir);
void		handle_double_redirect(t_shell *sh, t_redir *redir);
int			handle_quotes3(t_shell *sh, char *str, t_redir *redir);
void		not_redirect(t_shell *sh, t_args *args, t_tokens *tok);
int			process_quotes(t_shell *sh, t_args *args, t_tokens *tok);
int			find_quotes(t_shell *sh, char *str, int *start, int *end);
int			is_valid_redirect(t_args *args, t_tokens *tok, char *rdir);
int			handle_quotes(t_shell *sh, char *str, t_tokens *tok, int *end);
int			process_no_quotes(t_shell *sh, char *s, t_args *a, t_tokens *t);

#endif
