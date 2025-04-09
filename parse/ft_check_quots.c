#include "../minishell.h"

int    ft_check_end(char  *command, char  c)
{
    int    index;
    int    count;

    index = 0;
    count = 0;
    while (command[index])
    {
        if (command[index] == c)
            count++;
        index++;
    }
    if (count % 2 == 0)
        return (0);
    return (ft_syntax_error(), 1);
}

int    ft_check_quots(char *command)
{
    int     index;
    int     resault;

    index = 0;
    resault = 0;
    while (command[index])
    {
        if (command[index] == '\'')
        {
            resault = ft_check_end(command + index, '\'');
            index++;
            while (command[index] != '\'' && command[index])
                index++;
        }
        if (command[index] == '\"')
        {
            resault = ft_check_end(command + index, '\"');
            index++;
            while (command[index] != '\"' && command[index])
                index++;
        }
        index++;
    }
    return (resault);
}
