#include "../minishell.h"

void    ft_split_based(char **command, int index1, t_token **lst)
{
    int     i = 0;
    int     rest_point;
    char     *extraxted;
    t_token *tmp;
    bool     found_quots = false;
    
    while (command[index1][i])
    {
        if (command[index1][i] == '\"' || command[index1][i] == '\'')
        {
            found_quots = !found_quots;
            i++;
        }
        else if (!ft_strchr("|<>", command[index1][i]) && found_quots)
        {
            rest_point = i;
            while (!ft_strchr("|<>", command[index1][i]))
                i++;
            extraxted = ft_substr(command[index1], rest_point, i - rest_point);
            if (!extraxted)
                return ;
            tmp = ft_lstnew(ft_token_type(extraxted), extraxted);
            if (!tmp)
                return ;
            ft_lstadd_back(lst, tmp);
        }
        else
        {
            rest_point = i;
            while (ft_strchr("|<>", command[index1][i]))
                i++;
            extraxted = ft_substr(command[index1], rest_point, i - rest_point);
            if (!extraxted)
                return ;
            tmp = ft_lstnew(ft_token_type(extraxted), extraxted);
            if (!tmp)
                return ;
            ft_lstadd_back(lst, tmp);
        }
        i++;
    }
}
