/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 02:40:47 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/14 02:40:47 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// double quote / simple quote
# define SQ '\''
# define DQ '\"'

// error type
# define OK 0
# define ERROR 1
# define INVALID_INPUT 2

// error msg
# define STR_TIR "minishell: option requires an argument\n"
# define STR_NB_ARG "minishell: erreur: too many argument for exit code\n"
# define STR_WEX "minishell: wrong input for exit code\n"
# define STR_ERR "minishell: syntax error near unexpected token `"

// pour siginfo pour que y'ait pas les vagues
# define _POSIX_C_SOURCE_200809L

// include
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <signal.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include "../libft/libft.h"
# include <errno.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_in_minishell	t_shell;

//-------------------------------------- LEXER ---------------------------//
typedef enum enum_quote_state
{
	NO_Q,
	SQUOTE,
	DQUOTE
}	t_qstate;

typedef enum e_enum_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	NONO_CHAR,
	EXP
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
}	t_token;

// -------- LEXER FILE ------ //
// -> lexer.c
int		ft_lexer_check(char *line, t_token **tokens);
// -> lexer_error.c
// int		ft_has_nono_char(char *line);
int		ft_incomplete_quote(char *line);

// -------- UTILS FILE ------ //
// -> lexer_utils.c
void	ft_lexer_word(t_token **tokens, int *i, char *line);
void	ft_lexer_spe_char(t_token **tokens, int *i, char *s, t_type type);
void	ft_lexer_a_and_h(t_token **tokens, int *i, char *s, t_type type);
int		ft_is_spe_char(char c);
char	*ft_add_each_char(char *word, char c);
// -> lexer_utils2.c
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstnew_type(char *content, t_type type);
void	ft_lstfree(t_token *head);

//-------------------------------- SECOND CHANCE ---------------------------//
typedef struct s_sec_chance
{
	pid_t	pid;
	int		reading;
	int		writing;
	int		status;
	char	*all_line;
	int		bytes_read;
}	t_sec;

// --- SECOND_CHANCE FILE --- //
// -> second_chance.c
char	*ft_second_chance_parent(char *line, t_shell *shell);
void	ft_sc_child(char *line, int reading, int writing, t_shell *shell);
int		ft_needs_more(char *line);
// -> second_chance_helper.c
void	ft_exit_sc_child(char **line, char **n_l, int *w, t_shell *shell);
int		ft_malloc_sc(t_sec *s, char **line);
void	ft_exit_err_sig(t_shell *shell, int w, char **line);
// -------- UTILS FILE ------ //
// -> second_chance_utils.c
void	ft_init_second_chance(t_sec *s);
int		ft_clean_second_chance(t_shell *shell, t_sec *s);
void	ft_free_some(char **line, char **next_line, int *wri);
void	ft_null_next_line(char **line, int *wri, t_shell *shell);
void	ft_end_second_chance(char **line, int *writing);

//-------------------------------------- PARSING ---------------------------//
typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_HEREDOC,
	AST_APPEND,
	AST_ERROR,
}	t_ast_type;

typedef struct s_redir
{
	t_type			type_redir;
	char			*file;
	char			*heredoc_eof;
	bool			expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_ast_type		type;
	char			**args;
	bool			in_quote;
	struct s_ast	*left;
	struct s_ast	*right;
	t_redir			*redirs;
}	t_ast;

// ------- PARSING FILE ------ //
// -> parse_cmd.c
t_ast	*ft_parse_cmd(t_token *start, t_token *stop);
// -> parse_pipe.c
t_ast	*ft_parse_pipe(t_token *start, t_token *stop, t_token *pipe);
// -> parsing.c
t_ast	*ft_parse(t_token *start, t_token *stop);
int		ft_parsing_check(t_token **tokens, t_ast **ast, t_shell *shell);
char	*ft_rm_eof_q(char *eof);
// -> parsing_error.c
int		ft_error_input_pipe(t_token *token);
int		ft_error_input_redir(t_token *token);
int		ft_error_input_else(t_token *token);
char	*ft_type_to_str(t_token *token);
// -------- UTILS FILE ------ //
// -> parsing_utils.c
t_ast	*ft_lstnew_type_ast(t_ast_type type);
t_token	*ft_foundlast_redirs(t_token *start, t_token *stop);
t_token	*ft_foundlast_pipe(t_token *start, t_token *stop);
void	ft_free_ast(t_ast *ast);
int		ft_is_redir(t_token *token);
// -> parsing_utils2.c
t_redir	*ft_lstnew_type_redir(t_type type);
void	ft_lstadd_back_redir(t_redir **lst, t_redir *new);
void	ft_lstfree_redir(t_redir *head);
t_redir	*ft_lstlast_redir(t_redir *lst);
int		ft_has_no_quote(char *s);

//-------------------------------------- BUILT_IN ---------------------------//
typedef struct s_in_minishell
{
	int		last_exit_code;
	char	**build_env;
	bool	in_read_line;
	bool	in_pipe;
	bool	exit;
	bool	in_quote;
	char	*line;
	t_token	*token;
	t_ast	*ast;
}	t_shell;

typedef struct s_atoi
{
	long long			i;
	unsigned long long	result;
	unsigned long long	overflow;
	int					sign;
	int					nb;
}	t_atoi;

typedef struct s_close
{
	int	in;
	int	out;
}	t_close;

// -------- BUILT_IN FILE ---- //
// -> pwd.c
int		ft_builtin_pwd(t_shell *shell);
// -> env.c
int		ft_builtin_env(char **env);
// -> exit.c
int		ft_builtin_exit(char **args, t_shell *shell, t_close *c);
// -> cd.c
int		ft_builtin_cd(char ***env, char **arg);
// -> echo.c
int		ft_builtin_echo(char **args, t_shell *shell);
// -> export.c
int		ft_builtin_export(char ***env, char *arg);
int		ft_env_size(char **env);
// -> unset.c
int		ft_builtin_unset(char ***env, char *key);

// -------- UTILS FILE ------ //
// -> built_in_utils.c
int		ft_is_builtin(char *cmd);
int		ft_exec_built(t_ast *ast_node, char ***env, t_shell *shell, t_close *c);
int		ft_env_size(char **env);
void	ft_init_atoi(t_atoi *a);
// ->built_in_utils.c
int		ft_for_unset(t_ast *ast_node, char ***env);
int		ft_for_export(t_ast *ast_node, char ***env);
// -> env_utils.c
char	*ft_getenv(char **env, char *key);
char	**ft_copy_env(char **envp);
char	**ft_env_replace(char **env, char *key, char *new_entry);
int		ft_env_with_smt(t_ast *ast, t_shell *shell);

//-------------------------------------- EXPANS ----------------------------//
// --------- EPANS FILE ----- //
// ->expans.c
void	ft_exp_h(char **line, int std_out, t_redir *redir, t_shell *shell);
char	*ft_expand(char *line, t_shell *shell);
// -> expans_args.c
int		ft_handle_all(t_ast *ast, t_shell *shell);
// ->expans_helper.c
int		ft_quote_state(char c, t_qstate *state, int *i);
char	*ft_dollar(char *new, char *line, int *i, t_shell *shell);
void	ft_init_expand(int *i, t_qstate *state);
int		ft_handle_args(t_ast *ast, t_shell *shell);
void	ft_free_vars(char **var, char **var_content, char **word);
// -------- UTILS FILE ------ //
// -> expans_utils.c
char	*ft_return_var_content(t_shell *shell, char *var);
int		ft_len_var(char *var, int i);
void	ft_change_state(char c, t_qstate *state);
int		ft_is_quote(char c, t_qstate state);
char	*ft_get_var(char *line, int i);
// -> expans_utils2.c
char	*ft_add_str(char *word, char *line, int	*i, t_shell *shell);
char	*ft_string_exit_code(char *word, int *i, t_shell *shell);
bool	ft_has_quote(char *s);
void	ft_remove_empty_arg(char **args, int i);
void	ft_write_line(char **line, int std_out);
//-------------------------------------- EXEC ------------------------------//
typedef struct s_exec_heredoc
{
	char	*line;
	int		std_out;
	int		std_in;
	int		save_in;
	int		save_out;
	int		tty_in;
	int		tty_out;
}	t_exec_heredoc;

// --------- EXEC FILE ------ //
// -> exec.c
int		ft_exec_check(t_ast *ast, t_shell *shell);
int		ft_exec(t_ast *ast_node, t_shell *shell);
int		ft_exec_in_pipe(t_ast *ast_node, t_shell *shell);
void	ft_exit_enotdir(t_ast *ast, t_shell *shell);
// -> exec_cmd.c
void	ft_exec_cmd_child(t_ast *ast, t_shell *shell);
int		ft_exec_cmd(t_ast *ast, t_shell *shell);
void	ft_execve(t_ast *ast, t_shell *shell);
// -> exec_pipe.c
int		ft_exec_pipe(t_ast *ast_node, t_shell *shell);
int		ft_exec_cmd_pipe(t_ast *ast, t_shell *shell);
// -> exec_redir.c
int		ft_redir_choice(t_redir *redir, t_shell *shell);
int		ft_apply_redir(t_ast *ast, t_shell *shell);
int		ft_aply_no_c(t_ast *ast, t_shell *shell, int out_cpy, int in_cpy);
int		ft_no_c(t_redir *redir, t_shell *shell, int out_cpy, int in_cpy);
// -> exec_built_in.c
int		ft_builtin(t_ast *ast, t_shell *shell);
// -> redir.c
int		ft_exec_redir_out(t_redir *redir);
int		ft_exec_redir_in(t_redir *redir);
int		ft_exec_append(t_redir *redir);
int		ft_exec_heredoc(t_redir *redir, t_shell *shell);
int		ft_exec_heredoc_no_cmd(t_redir *redir);
// -> path.c
char	*ft_test_path(char *path, char *cmd, int *status);

// -------- UTILS FILE ------ //
// -> exec_utils.c
int		ft_close_fd(int *std_r, int *std_w, char *msg);
void	ft_exit(int *status, t_ast *ast, t_shell *shell);
int		ft_create_pipe(int *std_r, int *std_w);
void	ft_exit_slash(int *status, t_ast *ast, t_shell *shell);
// -> exec_utils2.c
void	ft_error_execve(char *path_cmd, t_ast *ast, t_shell *shell);
int		ft_wait(pid_t pid_in, pid_t pid_out);
int		ft_wait_cmd(pid_t pid);
int		ft_wait_no_eintr(pid_t pid, int *status);
// ->exec_utils3.c
void	ft_c_h_nocmd(int in_cpy, int out_cpy, t_redir *redir, t_shell *shell);
int		ft_cond(t_shell *shell, int in_cpy, int out_cpy, t_redir *redir);
int		ft_no_cmd_but_redir(t_ast *ast, t_shell *shell);
int		ft_no_cmd_clean(int *out_cpy, int *in_cpy);
// -> path_utils.c
char	*ft_extract_p(char **envp);
int		ft_contain_slash(char *s);
int		ft_access_return(char *path);
int		ft_is_a_directory(char *cmd);
char	*ft_return_status(int *found, int *status);
// -> exec_heredoc_utils.c
int		ft_for_sigint_heredoc(t_exec_heredoc *e, t_shell *shell);
void	ft_init_exec_heredoc(t_exec_heredoc *e);
int		ft_error_fd(t_exec_heredoc *e);
int		ft_end_exec_heredoc(t_exec_heredoc *e, t_redir *redir);
int		ft_begin_exec_heredoc(t_exec_heredoc *e, t_redir *redir);
// ->exec_heredoc_utils2.c
int		ft_reset_std(int std_in, t_redir *redir);
int		ft_norminette(t_exec_heredoc *e);
int		ft_loop_heredoc(t_exec_heredoc *e, t_shell *shell, t_redir *redir);

//-------------------------------------- SIGNAUX ---------------------------//
extern volatile sig_atomic_t	g_sig_received;

// -------- SIGNAL FILE ------ //
// -> signal.c
void	ft_handler(int signal);
void	ft_sig_readline_parent(t_shell *shell);
void	ft_handler_exec(int signal);
int		ft_sig_init(int sig, void (*handler_func)(int), int flags);
void	ft_handler_heredoc_child(int signal);
//-------------------------------------- CLEAN ------------------------------//
// -------- CLEAN FILE ------ //
// -> clean.c
int		ft_clean(t_token *head, t_ast *ast, t_shell *shell, int status);
void	ft_clean_at_exit(t_ast *ast, t_shell *shell);
void	ft_clean_at_end_cmd(t_token *tokens, t_ast *ast);
void	ft_clean_all_child(t_shell *shell, int nb);
// -> print_error.c
void	ft_print_err_msg_spe(char *input, char *msg, char *input1);
int		ft_print_error(t_token *token);
void	ft_print_err_msg(char *input, char *msg);
void	ft_print_err_msg_export(char *input, char *msg, char *input1);
void	ft_print_err_msg_heredoc(char *eof);
// -------- UTILS FILE ------ //
// -> error_utils.c
char	*ft_concat_error_str(char *err_msg, char *input);
char	*ft_concat_error_str_spe(char *err_msg, char *input, char *input1);
char	*ft_concat_error_str_export(char *err_msg, char *input, char *input1);
char	*ft_concat_error_str_he(char *eof_msg);

#endif