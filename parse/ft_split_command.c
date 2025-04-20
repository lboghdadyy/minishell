#include "../minishell.h"

int ft_lenght_sub(char *command, int index)
{
    int len;

    len = 0;
    while (!ft_strchr(" \'\"\t|", command[index]) && command[index])
    {
        index++;
        len++;
    }
    return (len);
}

t_tokentype ft_token_type(char *string)
{
    if (!string)
        return WORD;
    if (ft_check_pip(string))
        return PIPE;
    if (ft_check_redirect_in(string))
        return REDIRECT_IN;
    if (ft_check_redirect_out(string))
        return REDIRECT_OUT;
    if (ft_check_append(string))
        return APPEND;
    if (ft_check_heredoc(string))
        return HERDOC;
    if (ft_check_quotes_type(string) == SINGLE)
        return (SINGLEQ);
    if (ft_check_quotes_type(string) == COUPLE)
        return (DOUBLEQ);
    return WORD;
}

void    *ft_cleanup(t_token **lst, char **command)
{
    ft_lstclear(lst);
    free_tab(command);
    return NULL;
}

t_token *ft_split_command(char **command)
{
    t_token *lst;
    t_token *tmp;
    int     index;

    lst = NULL, tmp = NULL, index = 0;
    while (command[index])
    {
        tmp = ft_lstnew(ft_token_type(command[index]), command[index]);
        if (!tmp)
            ft_malloc(0, CLEAR);
        ft_lstadd_back(&lst, tmp);
        index++;
    }
    return (lst);
}
