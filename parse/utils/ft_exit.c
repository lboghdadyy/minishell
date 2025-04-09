#include "../../minishell.h"

void    ft_exit(char *error)
{
    if (error)
        write(2, error, ft_strlen(error));
    exit(1);
}