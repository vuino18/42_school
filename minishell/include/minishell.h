/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:52:00 by elino             #+#    #+#             */
/*   Updated: 2026/04/09 15:33:00 by alcarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_redir_type
{
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_redir_type;

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_OR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC
}	t_token_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				pipefd;
	int				quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		last_status;
	int		running;
	t_cmd	*cmds;
}	t_shell;

extern volatile sig_atomic_t	g_signal;

void		setup_signals_parent(void);
void		setup_signals_child(void);

t_env		*new_env_node(char *key, char *value);
void		append_node(t_env **head, t_env *node);
void		free_env(t_env *env);

t_env		*env_init(char **envp);
char		*get_env_value(t_env *env, char *key);
void		set_env_value(t_env **head, char *key, char *value);

char		**env_to_envp(t_env *env);

void		print_path_err(char *cmd, t_shell *shell);
char		*resolve_path(char *cmd, t_shell *shell);

int			setup_pipes(int pipefd[2]);
void		close_pipes(int pipefd[2]);

int			apply_redirs(t_redir *redirs);
void		apply_heredoc(t_redir *redir);

int			prepare_heredocs(t_cmd *cmds, t_shell *shell);
void		close_heredoc_fds(t_cmd *cmds);

void		heredoc_child(int wfd, char *delim, int quoted, t_shell *sh);

int			is_builtin(char *cmd);
int			exec_builtin(t_cmd *cmd, t_shell *shell);
void		child_exit(t_shell *shell, int code);
void		run_child(t_cmd *cmd, t_shell *shell, int prev_fd, int *pipefd);
int			execute_pipeline(t_cmd *cmds, t_shell *shell);

void		setup_child_fds(int prev_fd, int *pipefd);
int			run_pipeline(t_cmd *cmds, t_shell *shell);
int			exec_parent_builtin(t_cmd *cmd, t_shell *shell);

void		exec_external(t_cmd *cmd, t_shell *shell);

int			fork_one(t_cmd *cur, t_shell *shell, int *prev_fd, pid_t *last_pid);
int			collect_status(pid_t last_pid);

int			line_needs_more(char *line);
char		*read_full_line(char *first, t_shell *shell);
void		shell_loop(t_shell *shell);

int			process_line(t_shell *shell, char *line);
char		*rfl_join(char *joined, char *cont);
int			lnm_update_quote(int state, char c);
void		loop_iter(t_shell *shell, char *line);
void		lnm_handle_pipe(char *line, int *i, int *last_pipe, int *seen_word);

t_token		*new_token(t_token_type type, char *value);
t_token		*lexer(char *line);
void		free_tokens(t_token *tokens);

t_token		*tok_operator(char *s, int *i);

char		*join_free(char *a, char *b);
char		*expand_dollar(char *s, int *i, t_shell *sh);
char		*expand_word(char *s, t_shell *sh);

void		expand_tokens(t_token *toks, t_shell *sh);

t_redir		*new_redir(t_token_type type, char *file);
t_cmd		*new_cmd(void);
void		free_cmds(t_cmd *cmds);

int			check_pipe_tok(t_token *cur, int prev_is_pipe);
void		unlink_tok(t_token **toks, t_token **prev, t_token **cur);
const char	*tok_name(t_token *tok);
int			syntax_error(const char *token_str);

int			check_syntax(t_token *toks);
void		remove_empty_tokens(t_token **toks);
t_cmd		*parse_input(char *line, t_shell *shell);

t_cmd		*build_pipeline(t_token *toks);

int			is_builtin(char *cmd);

int			builtin_echo(t_cmd *cmd, t_shell *shell);
int			builtin_cd(t_cmd *cmd, t_shell *shell);
int			builtin_pwd(t_cmd *cmd, t_shell *shell);
int			builtin_env(t_cmd *cmd, t_shell *shell);
int			builtin_export(t_cmd *cmd, t_shell *shell);
int			builtin_unset(t_cmd *cmd, t_shell *shell);
int			builtin_exit(t_cmd *cmd, t_shell *shell);

void		parse_sign(char *str, int *i, int *neg);
int			is_numeric(char *str);
int			is_overflow(char *str);
int			get_exit_code(char *str);

#endif
