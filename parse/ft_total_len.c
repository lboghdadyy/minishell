#include "../minishell.h"

size_t  ft_total_len(char   *value)
{
    int index;
    size_t count;
    char    *sub;
    char    *found;

    count = 0;
    index = 0;
    while (value[index])
    {
        if (value[index] == '$')
        {
            sub = ft_substr(value, index + 1, skip_variable(value, index));
            found = getenv(sub);
            count += ft_strlen(found);
            // free(sub);
            index += skip_variable(value, index);
        }
        else if (value[index] == '\'' || value[index] == '\"')
            index++;
        else
        {
            count++;
            index++;
        }
    }
    return (count);
}
