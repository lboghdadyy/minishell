#include "../../minishell.h"

void    ft_syntax_error()
{
    write(2, "Syntax error\n", 13);
}