/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:45:16 by sde-carv          #+#    #+#             */
/*   Updated: 2024/12/15 20:38:13 by ptchipoc         ###   ########.fr       */
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
# include "libft/inc/libft.h"

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
	char	**file;
	int		control;
	int		left_fd;
	char	**redir;
	char	**matrix;
	char	*arg[1024];
	char	**left_file2;
	char	**left_file;
	char	*left_double_file[1024];
	char	**left_double_file2;
	char	**first_left_file;
	char	**mat2;
	char	**arg_left;
	char	**dell_double;
	char	**dell_double2;
	char	**heredoc_arg;
	char	**heredoc_delimiter;
	char	**heredoc_delimiter2;
	char	**doc_tree_position;
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
	int		pip;
	int		flag;
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
	int		n_rdir[1000];
	char	*temp_unset[1024];
	char	**temp_unset2;
}	t_shell;

int			s_quotes(int c);
int			get_var(int value);
int			get_var2(int value);
void		signal_handler3(int sig);
int			herepipe(t_shell *sh, int *i);
int			valid_quotes(t_shell *sh, char *str);

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
int			end_with_equals(char *str);
void		cmd_export(char **env);
void		print_equals_end(char *str);
int			found_equals(char *str);
void		cmd_export2(t_shell *sh);
int			valid_env_name(char *str);
void		ch_value(char **env, char *str);
void		add_var(t_shell *sh, char *str);
int			check_envi(char **env, char *str);
void		export_error(char *str);

// Utils
void		free_mat(char **mt);
int			matrix_line(char **mt);
void		print_matrix(char **matrix);
char		*ft_strndup(const char *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);

// Unset
void		free_args(t_shell *sh);
void		filter_tokens(char **mat);
void		free_array_mat(char ****array);
void		cmd_unset(t_shell *sh, char **to_remove);

// Exec_cmd
int			exec_cmd(t_shell *sh);
char		**ft_args(t_args *args);
void		signal_handler2(int sig);
void		child_process(t_shell *sh);
char		**ft_strjoin_alt(char **spl, char *s);
int			handle_child_process(t_shell *sh, pid_t pid);
int			print_error(t_shell *sh, char *message, int status);
void		handle_exec_error(char *tmp, char **arg, t_shell *sh);

// Others
int			ft_isspace(char c);
int			ft_get_digit(char c);
int			ft_status(int status);
void		exec_abs(t_shell *sh);
int			is_special_char(char c);
int			file_dt_error(t_shell *sh);
int			validate_input(t_shell *sh);
int			check_syntax_error(t_shell *sh);
int			handle_syntax_error(char *token);
int			is_empty_input(const char *input);
int			check_pipe_syntax(t_shell *sh, char *input, int *i);
void		xprint(char *str, char *str2, int fd);
int			check_redirect_syntax(char *input, int *i);
int			ft_alter_strchr(t_shell *sh, char *str, char c);
long long	ft_strtoll(const char *str, char **endptr, int base);

// Expansions
char		*get_name(char *str, int j);
int			is_in_quotes(int *state, char c);
char		*get_env(t_shell *sh, char *str);
int			states_cmd(t_shell *sh, t_args *args, int i, int j);
char		*not_found(t_args *args, char *name, int *i, int j);
void		expansion(t_shell *sh, t_args *args, t_tokens *tok);

// Redirects
void		get_dir(t_shell *sh);
void		get_arg(t_shell *sh);
void		get_file(t_shell *sh);
void		allocater(t_shell *sh);
void		left_oper(t_shell *sh);
void		exec_left(t_shell *sh);
void		operators(t_shell *sh);
void		right_oper(t_shell *sh);
void		exec_right(t_shell *sh);
void		double_left(t_shell *sh);
void		help_get_arg(t_shell *sh);
void		get_left_file1(t_shell *sh);
void		redir_first(t_shell *sh);
void		with_file(t_shell *sh);
void		first_double_left(t_shell *sh);
void		put_in_delldoble(t_shell *sh);
void		help_with_file(t_shell *sh);
void		get_left_file2(t_shell *sh);
void		get_double_file(t_shell *sh);
void		help_double_left(t_shell *sh);
void		two_positions(t_shell *sh);
void		tree_positions(t_shell *sh);
void		only_delimiter(t_shell *sh);
void		when_unordered(t_shell *sh);
void		when_ordered(t_shell *sh);
void		fill_heredoc_delimiter(t_shell *sh);
void		fill_heredoc_arg(t_shell *sh);
void		more_than_tree_positions(t_shell *sh);
void		in_first_position(t_shell *sh);
void		fill_heredoc_delimiter2(t_shell *sh);
void		tree_positions2(t_shell *sh);
void		fill_heredoc_tree_position(t_shell *sh);
void		firsts_left_file(t_shell *sh);
void		exec_exit(t_shell *sh);
void		exec_exit2(t_shell *sh, int *i);
void		help_help_when_ordered1(t_shell *sh);
void		help_help_when_ordered(t_shell *sh);
void		help_when_unordered(t_shell *sh);
void		other_position(t_shell *sh);
void		more_than_tree_positions2(t_shell *sh);
int			is_word(char *str);
int			is_command(const char *cmd);
int			is_redir(char *str);
int			find_type(t_shell *sh);
int			find_file(t_shell *sh);
int			help_redir_first(t_shell *sh);
int			verify_status2(t_shell *sh);
int			flag_to_status2(t_shell *sh);
int			type_of_redir(char **mt);
int			help_get_dir(t_shell *sh);
int			help_get_file(t_shell *sh);
int			verify_status(t_shell *sh);
int			help_right(t_shell *sh, int *fd);
int			has_redir(t_shell *sh, char **mt);

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
