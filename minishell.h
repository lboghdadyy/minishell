#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>

typedef enum e_tokentype {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_SEMICOLON,
}	t_tokentype;

typedef struct s_token {
	t_tokentype		type;
	char			*value;
	struct s_token	*next;
}	t_token;

void		ft_exit(char *error);
int			ft_check_quots(char *command);
size_t		ft_strlen(char *str);
void		ft_parse_command(char *string);
char		*ft_strjoin(char *s1, char *s2);
void		ft_syntax_error(void);
char		*ft_substr(char *s, unsigned int start, size_t len);
t_token		*ft_split_command(char **command);
char		*ft_strchr( char *s, int c);
t_token		*ft_lstnew(t_tokentype type, char *value);
t_token		*ft_lstlast(t_token *lst);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		ft_lstclear(t_token **lst);
int			ft_is_space(char c);
char		**ft_split(char *s);
void		free_tab(char **str);
int			ft_is_space(char c);
bool		ft_check_pip(char *string);
bool		ft_check_redirect_in(char *string);
bool		ft_check_redirect_out(char *string);
bool		ft_check_semicolon(char *string);
bool		ft_check_append(char *string);
t_tokentype	ft_token_type(char *string);
void		ft_split_based(char **command, int index1, t_token **lst);
char		*ft_strdup(char *src);

#endif