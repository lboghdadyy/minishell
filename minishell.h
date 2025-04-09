# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

typedef struct c_list{
    char    *value;
    // t_token_type    type;
    struct  c_list *next;
} t_list;

// typedef enum e_token_type {
//     TOKEN_WORD,
//     TOKEN_PIPE,
//     TOKEN_REDIRECT_IN,
//     TOKEN_REDIRECT_OUT,
//     TOKEN_APPEND,
//     TOKEN_HEREDOC
// } t_token_type;

void    ft_exit(char *error);
int    ft_check_quots(char *command);
size_t  ft_strlen(char *str);
void    ft_parse_command(char *string);
char	*ft_strjoin(char *s1, char *s2);
void    ft_syntax_error();

# endif