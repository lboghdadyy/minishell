#include "../minishell.h"

char* token_type_to_string(t_tokentype type) {
    if (type == TOKEN_WORD) {
        return "WORD";
    }
    else if (type == TOKEN_PIPE) {
        return "PIPE";
    }
    else if (type == TOKEN_REDIRECT_IN) {
        return "REDIRECT_IN";
    }
    else if (type == TOKEN_REDIRECT_OUT) {
        return "REDIRECT_OUT";
    }
    else if (type == TOKEN_APPEND) {
        return "APPEND";
    }
    else if (type == TOKEN_SEMICOLON) {
        return "SEMICOLON";
    }
    else {
        return "UNKNOWN";
    }
}

void print_token_list(t_token *head) {
    while (head) {
        printf("Type: %s | Value: %s\n", token_type_to_string(head->type), head->value);
        head = head->next;
    }
}

void    ft_parse_command(char *string)
{
    t_token *lst;
    if (string[0])
    {
        if (ft_check_quots(string) == 1)
            return ;
        lst = ft_split_command(ft_split(string));
        if (!lst)
            return ;
        print_token_list(lst);
    }
}