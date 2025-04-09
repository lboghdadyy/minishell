#include "../minishell.h"

void    ft_parse_command(char *string)
{
    
    if (string[0])
    {
        if (ft_check_quots(string) == 1)
            return ;
    }
}