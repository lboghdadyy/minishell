/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:22 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/29 12:15:57 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define SINGLE 20
# define COUPLE 10
# define RED_OUT 30
# define RED_IN 31
# define APPE 32
# define HERED 33
# define ALLOC 1
# define CLEAR 2
# define WHITE "\033[0;37m"
# define RED "\033[0;31m"

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;

}	t_garbage;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef enum e_tokentype {
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	APPEND,
	HERDOC,
	DOUBLEQ,
	SINGLEQ,
	DELEMTER,
}	t_tokentype;

typedef struct s_expand
{
	bool	s_q;
	bool	d_q;
	int		i;
}	t_expand;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token {
	t_tokentype		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*previous;
	int				fd_reder;
}	t_token;

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	char			*cmd;
	char			**opt;
	struct s_exec	*next;
	int				flag;			
}	t_exec;

typedef struct s_main_ctx
{
	char	*input;
	char	*expn;
	t_token	*lst;
	t_exec	*exec;
	t_env	*envp;
}	t_main_ctx;

typedef struct s_expand_ctx
{
	char		*nv;
	char		*sub;
	int			b_x;
	bool		r;
	t_expand	e;
	t_env		*envp;
	char		*s;
	int			st;
}	t_expand_ctx;

typedef struct s_heredoc_ctx
{
	char	*f;
	int		fd_out;
	int		fd_in;
	int		st;
	int		pid;
}	t_heredoc_ctx;

typedef struct s_cut
{
	t_token	*tmp;
	int		pip_i;
}	t_cut;

int			ft_check_quotes_type(char *string);
int			ft_check_quots(char *command);
size_t		ft_strlen(char *str);
int			ft_parse_command(char *string);
char		*strj(char *s1, char *s2);
void		ft_syntax_error(void);
char		*subs(char *s, unsigned int start, size_t len);
t_token		*s_cmd(char **command, t_env *envp);
char		*ft_strchr( char *s, int c);
t_token		*ft_lstnew(t_tokentype type, char *value);
t_token		*ft_lstlast(t_token *lst);
void		ft_lstadd_back(t_token **lst, t_token *new);
int			ft_is_space(char c);
char		**ft_split(char *s);
int			ft_is_space(char c);
bool		ft_check_pip(char *string);
bool		ft_check_redirect_in(char *string);
bool		ft_check_redirect_out(char *string);
bool		ft_check_append(char *string);
t_tokentype	ft_token_type(char *string);
char		*ft_strdup(char *src);
bool		ft_check_heredoc(char *string);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *s1, char *s2, size_t n);
int			skip_variable(char *value, int index);
void		ft_expand(t_token *lst, t_env *envp);
int			ft_handle_heredoc(t_token *lst, t_env *env, int fd_out);
char		*exp_val(char *value, t_env *envp, int status);
char		*g_env(char *value, int *index, t_env *envp);
int			ft_check_braces(char *string);
char		*ft_remove_bracets(char *string);
int			check_br(char *string);
int			ft_stop_redirect(t_token *lst, t_env *envp);
char		*get_next_line(char *prompt);
void		handler(int sig);
bool		should_expand(char *s, t_expand e);
int			delimter(char *s, size_t index);
bool		is_invalid_dollar_after_op(t_expand_ctx *c);
void		del_token_node(t_token **head, t_token *node_to_delete);
void		ambigous_red(void);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
// garbage
void		*ft_malloc(size_t size, int flag);
// exec_child
void		setup_child(int *fd, t_env *path, t_exec *head, int bltn);
int			parent_thing(int *fd, t_exec *head);
void		cmd_not_found(char *cmd);
int			check_exit_status(void);
int			ignore_first_cmd(int res, int get);

// exec
int			execution(t_exec *exec, t_env **env);
int			execute_cmd(t_exec *head, t_env **env);
char		*get_cmd_path(char *cmd, char *path);
int			is_empty(char *s);
void		call_execve(t_exec *head, t_env *env);

//parse_to_exec_more
int			handle_heredoc(t_token **lst, t_exec *node, t_env *env);
int			handle_redirect_in(t_token **lst, t_exec *node);
int			handle_append(t_token **lst, t_exec *node);
int			handle_redirect_out(t_token **lst, t_exec *node);

//parse_to_exec
int			count_until_pipe(t_token *lst);
void		handle_word(t_token *lst, t_exec *node, int *i);
int			handle_redirects(t_token **lst, t_exec *node, t_env *env);
int			fill_node(t_token **lst, t_exec *node, t_env *env);
t_exec		*convert_token_to_exec(t_token *lst, t_env *env);

// ft_split_exec
char		**ft_split_exec(char const *s, char c);

//  exec_utils
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strstr(char *str, char *to_find);

// exec_list
int			ft_lstsize_env(t_env *env);
t_exec		*new_node(void);
void		ft_lstadd_back_exec(t_env **lst, t_env *new);

//exec_more_list
int			ft_lstsize(t_exec *exec);
t_env		*ft_lstnew_exec(char *key, char *value);
t_env		*ft_lstlast_exec(t_env *lst);
void		add_back(t_exec **head, t_exec *new);

// export more
int			is_valid_export(char *opt);
void		swap_env(t_env *a, t_env *b);
void		bubble_sort_env(t_env *env);
void		print_sorted_env(t_env *env, int fd);

// export
void		handle_plus_equal(char *opt, t_env **env);
void		handle_equal_or_none(char *opt, t_env **env);
int			ft_export(char **opt, t_env **env, int fd);

//unset
void		delet_node(t_env **env, char *key);
void		ft_unset(char **opt, t_env **env);

//echo
int			is_valid_option(char *str);
int			ft_echo(char **cmd, int fd);

//env
void		init_default_env(t_env **env, char *pwd);
t_env		*init_env(char **envp);
char		*get_env_value(t_env **env, char *path);
t_env		*find_env(t_env	*env, char *key);
int			ft_env(t_env *env, int fd);

// itoa
char		*ft_itoa(int n);
int			ft_atoi(const char *str, int *flag);

// cd
void		update_oldpwd(t_env **env, char *oldpwd);
void		getcwd_fail(char *path, t_env **env, char **hold_pwd, char *newpwd);
int			change_dir(char *path, t_env **env, char **hold_pwd);
char		*ft_cd(char **opt, t_env **env);

// exit
int			is_valid_exit(char	*opt);
int			ft_exec_exit(char **opt, bool forked);
int			e_status(int sts, int set);

//builtins
int			is_builtin(char *cmd);
char		**convert_t_env(t_env *env);
void		execute_builtin(t_exec *exec, t_env **env, bool forked);

// pwd
int			ft_pwd(t_env *env, int fd);
int			pwd_and_oldpwd(t_env *env, int fd);
char		*ft_strdup2(char *src);

void		handler(int sig);
void		handle_sigint(int sig);

void	ft_remove_quotes(t_token *tmp);
int			delimter(char *s, size_t index);
void		handl_sig(int sig);

#endif