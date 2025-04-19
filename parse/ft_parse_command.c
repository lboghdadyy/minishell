#include "../minishell.h"

char* token_type_to_string(t_tokentype type)
{
    if (type == PIPE) {
        return "PIPE";
    }
    else if (type == REDIRECT_IN) {
        return "REDIRECT_IN";
    }
    else if (type == REDIRECT_OUT)
        return "REDIRECT_OUT";
    else if (type == APPEND)
        return "APPEND";
    else if (type == HERDOC)
        return ("HEREDOC");
    else
    {
        return "WORD";
    }
}

void print_token_list(t_token *head) {
    while (head) {
        printf("Type: %s | Value: %s\n", token_type_to_string(head->type), head->value);
        head = head->next;
    }
}

int     ft_count_operator(char *string, int index, char c)
{
    int count;

    count = 0;
    while (string[index] == c)
    {
        count++;
        index++;
    }
    return count;
}

int ft_check_syntax(char *string)
{
    int index;

    index = 0;
    while (string[index])
    {
        if (string[index] == '<' || string[index] == '>')
        {
            if (ft_count_operator(string, index, string[index]) > 2)
                return (ft_syntax_error(), 1);
        }
        index++;
    }
    return 0;
}

t_token    *ft_parse_command(char *string)
{
    t_token *lst;
    
    lst = NULL;
    if (string)
    {
        if (ft_check_quots(string))
            return (NULL);
        if (ft_check_syntax(string))
            return (NULL);
        lst = ft_split_command(ft_split(string));
        if (!lst)
            return (NULL);
        if (ft_logic_syntax(lst))
            return (ft_lstclear(&lst), NULL);
        // ft_expand(lst);
    }
    return (lst);
}