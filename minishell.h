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

// garbage
# define ALLOC 1
# define CLEAR 2

# define SINGLE 20
# define COUPLE 21


void	*ft_malloc(size_t size, int flag);
int		clear_fds(int fd, int save);

typedef struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

typedef enum e_tokentype {
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HERDOC,
	DOUBLEQ,
	SINGLEQ,
}	t_tokentype;

typedef struct s_token {
	t_tokentype		type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	char			*cmd;
	char			**opt;
	struct s_exec	*next;
}	t_exec;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// parsing
void		ft_exit(char *error);
int			ft_check_quots(char *command);
size_t		ft_strlen(char *str);
t_token		*ft_parse_command(char *string);
char		*ft_strjoin(char *s1, char *s2);
void		ft_syntax_error(void);
char		*ft_substr(char *s, unsigned int start, size_t len);
t_token		*ft_split_command(char **command);
char		*ft_strchr(char *s, int c);
t_token		*ft_lstnew(t_tokentype type, char *value);
t_token		*ft_lstlast(t_token *lst);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		ft_lstclear(t_token **lst);
int			ft_is_space(char c);
char		**ft_split(char *s);
void		free_tab(char **str);
bool		ft_check_pip(char *string);
bool		ft_check_redirect_in(char *string);
bool		ft_check_redirect_out(char *string);
bool		ft_check_append(char *string);
bool		ft_check_heredoc(char *string);
t_tokentype	ft_token_type(char *string);
void		ft_split_based(char **command, int index1, t_token **lst);
char		*ft_strdup(char *src);
int			ft_logic_syntax(t_token *lst);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
char		*ft_strstr(char *haystack, char *needle);
size_t		ft_strlcat(char *s1, char *s2, size_t n);
int			ft_check_quotes_type(char *string);
void		ft_expand(t_token *lst);
int			skip_variable(char *value, int index);
size_t		ft_total_len(char *value);

// exec
void		execution(t_exec *exec, t_env **env, char **envp);
int			ft_lstsize(t_exec *exec);
int			is_builtin(char *cmd);
void		execute_builtin(t_exec *exec, t_env **env, char **envp);
t_exec		*convert_token_to_exec(t_token *lst);
int			count_until_pipe(t_token *lst);

// builtins
int			ft_echo(char **opt);
int			ft_env(char **env);
int			ft_cd(char **opt, t_env **env);
int			ft_pwd(void);

// export / unset
t_env		*init_env(char **envp);
t_env		*find_env(t_env *env, char *key);
int			ft_export(char **opt, t_env **env);
int			is_valid_export(char *opt);
void		ft_unset(char **opt, t_env **env);
int			ft_exec_exit(char **opt);

// exec_utils
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);

// exec_list
int			ft_lstsize(t_exec *exec);
t_exec		*new_node(void);
void		add_back(t_exec **head, t_exec *new);
void		ft_lstadd_back_exec(t_env **lst, t_env *new);
t_env		*ft_lstnew_exec(char *key, char *value);
t_env		*ft_lstlast_exec(t_env *lst);

#endif
