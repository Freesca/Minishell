/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonati <fdonati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:15:19 by fdonati           #+#    #+#             */
/*   Updated: 2024/06/23 14:18:00 by fdonati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef enum e_env_type
{
	ENV_VAR,
	EXP_VAR,
	HDN_VAR,
}	t_env_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	t_env_type		type;
	struct s_env	*next;
}			t_env;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_COMMAND,
	T_LIM,
	T_LIM_QUOTE,
	T_FD,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}			t_token;

typedef struct s_cmd
{
	int				*redir_in;
	int				*redir_out;
	char			**args;
	char			*path;
	char			**path_hc;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_data
{
	int		original_stdin;
	int		original_stdout;
	int		pipe_fd[2];
	int		fd_in;
}				t_data;

extern int	g_exit_status;

t_env	*ft_env_init(char **envp);
int		ft_update_status(int status, t_env **envp);

void	ft_free_mtx(char **mtx);
void	ft_free_n_err(int err, t_token **token, t_cmd **cmd, t_env **envp);
void	ft_free_n_exit(int err, t_token **token, t_cmd **cmd, t_env **envp);

int		ft_tokenize(char *line, t_token **token, t_env *envp);
int		ft_word(t_token **token, char *line, int *i, int *cmd_count);
int		ft_word_fd(t_token **token, char *line, int *i);
int		ft_special_char(t_token **token, char *line, int *i, int *cmd_count);
int		ft_word_end(char *line, int *i);
char	*ft_quote_clean(char *str);

int		ft_lexer(t_token **token);

int		ft_command(t_token **token, t_cmd **cmd, t_env **envp);
int		ft_command_init(t_cmd **cmd, t_token *token, t_env **envp);
int		ft_command_fill(t_cmd *cmd, t_token *token, t_env **env,
			int (*f)(t_cmd *, t_token *, t_env **));
int		ft_args_init(t_cmd *cmd, t_token *token, t_env **envp);
int		ft_hc_init(t_cmd *cmd, t_token *token, t_env **envp);
int		ft_redir_init(t_cmd *cmd, t_token *token, t_env **envp);
int		ft_addpath(char *value, char **path, t_env **envp);
int		ft_addarg(char *value, char ***args);
int		ft_addheredoc(char **lim_to_strhc,
			char ***path_hc, int quote, t_env *envp);
int		ft_addredir(t_token_type type, char *value, int **redir);

int		ft_exec(t_cmd **cmd, t_env **envp, t_data *data);
void	ft_exec_child(t_cmd **cmd, t_env **envp,
			t_data *data, int cmd_count);
int		ft_redir(t_cmd **cmd);
void	ft_pipe(t_cmd *cmd, t_data *data, int *cmd_count, int pid);

int		ft_is_builtin(t_cmd *cmd);
int		ft_exec_builtin(t_cmd **cmd, t_env **envp, t_data *data, int cmd_count);
int		ft_exec_builtin_solo(t_cmd **cmd,
			t_env **envp, t_data *data, int cmd_count);
int		ft_echo(t_cmd *cmd);
int		ft_exit(t_cmd **cmd, t_env **envp, int cmd_count);
int		ft_env(t_cmd *cmd, t_env *envp);
int		ft_export(t_cmd *cmd, t_env **envp);
int		ft_export_lexer(char *str);
int		ft_unset(t_cmd *cmd, t_env **envp);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd, t_env **envp);
int		ft_cd_lexer(t_cmd *cmd);

int		ft_change_value(t_env **env, char *key, char *value, int flag);
char	*ft_swap_envp(char *line, t_env *envp);
char	*ft_process_env_var(char *line, int start, int *i, t_env *envp);
void	ft_find_env_var_end(const char *line, int *i);
int		ft_skip_single_quotes(const char *line, int i);
char	*ft_swap_envp_hc(char *line, t_env *envp);
char	*ft_swap_scroll_hc(char *line, int *i, t_env *envp, int flag_lim);
char	*ft_swap_value(char *line, int start, int end, t_env *envp);
char	*ft_get_envp_value(const char *key, t_env *envp);
char	*ft_special_quote(char *str);
char	**ft_env_to_mtx(t_env *envp);

t_token	*ft_lstnew_t(t_token_type type, char *value);
t_token	*ft_lstlast_t(t_token *list);
void	ft_lstclear_t(t_token **list);
void	ft_lstadd_back_t(t_token **list, t_token *new);

void	ft_lstadd_back_c(t_cmd **list, t_cmd *new);
void	ft_lstclear_c(t_cmd **list);
void	ft_lstunlink_c(char **path_hc);
void	ft_lstcut_c(t_cmd **cmd);
t_cmd	*ft_lstnew_c(void);

void	ft_lstaddback_e(t_env **list, t_env *new);
void	ft_lstclear_e(t_env **list);
t_env	*ft_lstnew_e(char *str, t_env_type type);
int		ft_key_n_value(char *str, char **key, char **value);

/* typedef struct s_exec
{
	char	**cmd;
	char	**path;
	char	*path_ok;
}			t_exec;

typedef struct s_data
{
	int		infile;
	int		outfile;
	int		pipe_nbr;
	int		original_stdin;
	int		original_stdout;
	bool	redirect_out;
}				t_data; */

/* void	ft_free_mat(char **mat);
void	ft_print_token(t_token *token);
int		ft_is_command(char *cmd, char **envp);
char	**ft_split_cmd(char *str, char c);
void	ft_tokenize(char *line, t_token **token, char **envp);
t_token	*ft_parcing(t_token *token);
int		ft_error_no_cmd(t_token *token);
int		ft_command(t_token *token, char	**envp);
int		ft_execute(t_token *token, char **envp, t_data data);
int		ft_redirect(t_token **token, t_data *data);


t_token	*ft_create_node(t_token_type type, char *value);
t_token	*ft_create_list(int argc, char **argv);
t_token	*ft_list_last(t_token *list);
void	ft_free_list(t_token *list);
void	ft_list_addfront(t_token **list, t_token *new);
void	ft_list_addback(t_token **list, t_token *new);
t_token	*ft_list_find_node(t_token *list, char *token); */

# define PROMPT "minishell$ "
# define BUILTINS 7
# define MAX_PATH 4096
# define MAX_CMD 4096
# define MAX_ARG 4096
# define MAX_ENV 4096
# define MAX_VAR 4096
# define MAX_BUILTIN 4096
# define MAX_PIPE 4096
# define MAX_REDIRECTION 4096

#endif
