#include "../minishell.h"

int ft_logic_syntax(t_token *lst)
{
    t_token *tmp;

    tmp = lst;
    while (tmp)
    {
        if (tmp->type == TOKEN_PIPE && tmp->next->type != TOKEN_WORD)
            return (ft_syntax_error(), 1);
        if (tmp->type == TOKEN_HERDOC && tmp->next->type != TOKEN_WORD)
            return (ft_syntax_error(), 1);
        if (tmp->type == TOKEN_REDIRECT_IN && tmp->next->type != TOKEN_WORD)
            return (ft_syntax_error(), 1);
        if (tmp->type == TOKEN_REDIRECT_OUT && tmp->next->type != TOKEN_WORD)
            return (ft_syntax_error(), 1);
        if (tmp->type == TOKEN_APPEND && tmp->next->type != TOKEN_WORD)
            return (ft_syntax_error(), 1);
        tmp = tmp->next;
    }
    return 0;
}