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
        return TOKEN_WORD;
    if (ft_check_pip(string))
        return TOKEN_PIPE;
    if (ft_check_redirect_in(string))
        return TOKEN_REDIRECT_IN;
    if (ft_check_redirect_out(string))
        return TOKEN_REDIRECT_OUT;
    if (ft_check_append(string))
        return TOKEN_APPEND;
    if (ft_check_heredoc(string))
        return TOKEN_HERDOC;
    return TOKEN_WORD;
}

void    *ft_cleanup(t_token **lst, char **command)
{
    ft_lstclear(lst);
    free_tab(command);
    return NULL;
}

t_token *ft_split_command(char **command)
{
    int index;
    int index2;
    t_token *lst;
    t_token *new_node;
    bool special_char_found;

    if (!command)
        return NULL;
    index = 0;
    lst = NULL;
    new_node = NULL;
    special_char_found = false;
    index2 = 0;
    while (command[index])
    {
        special_char_found = false;
        index2 = 0;
        while (command[index][index2] && !special_char_found)
        {
            if (ft_strchr("|<>", command[index][index2]))
            {
                special_char_found = true;
                ft_split_based(command, index, &lst);
                break;
            }
            index2++;
        }
        if (!special_char_found)
        {
            new_node = ft_lstnew(ft_token_type(command[index]), 
            ft_strdup(command[index]));
            if (!new_node)
                return ft_cleanup(&lst, command);
            ft_lstadd_back(&lst, new_node);
        }
        index++;
    }
    return lst;
}
