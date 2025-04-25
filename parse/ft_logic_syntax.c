#include "../minishell.h"

int ft_logic_syntax(t_token *lst)
{
    t_token *tmp;
    t_token *next;
    t_token *previous;

    tmp = lst;
    while (tmp)
    {
        next = tmp->next;
        previous = tmp->previous;
        if (tmp->type == PIPE && (!next || next->type == PIPE || !previous))
            return (ft_syntax_error(), 1);
        if (tmp->type == HERDOC && (!next || next->type != WORD))
            return (ft_syntax_error(), 1);
        if (tmp->type == REDIRECT_IN && (!next || next->type != WORD))
            return (ft_syntax_error(), 1);
        if (tmp->type == REDIRECT_OUT && (!next || next->type != WORD))
            return (ft_syntax_error(), 1);
        if (tmp->type == APPEND && (!next || next->type != WORD))
            return (ft_syntax_error(), 1);
        tmp = tmp->next;
    }
    return 0;
}
