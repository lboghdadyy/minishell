#include "../minishell.h"

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
    int count;

    index = 0;
    count = 0;
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
            return (NULL);
    }
    return (lst);
}
