#include "../../minishell.h"

size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        i++;
    }
    return (i);
}