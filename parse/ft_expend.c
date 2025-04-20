#include "../minishell.h"

int skip_variable(char *value, int index)
{
    int count;

    count = index + 1;
    while (value[count] && !ft_strchr("\" $", value[count]))
        count++;
    return (count - index);
}

size_t ft_len_wo_variable(char *value)
{
    int index;
    size_t count;

    index = 0;
    count = 0;
    while(value[index])
    {
        if (value[index] == '$')
            index += skip_variable(value, index);
        else
        {
            index++;
            count++;
        }
    }
    return (count);
}

void	ft_get_env(char *new_value, t_token *lst, int *r, int *index)
{
	int		i = 0;
	char	*sub;
	char	*found;
	size_t	skipped;

	skipped = skip_variable(lst->value, *index);
    sub = ft_substr(lst->value, *index + 1, skipped - 1);
	*index += skipped;
	found = getenv(sub);
	free(sub);
	if (!found)
		return;
	while (found[i])
	{
        new_value[*r] = found[i];
		i++;
		(*r)++;
	}
    new_value[*r] = '\0';
}

void    ft_expand_value(t_token *lst)
{
    char    *new_value;
    int     r = 0;
    int     index = 0;
    bool    in_single_quote = false;
    size_t  total_len = ft_total_len(lst->value);

    if (!ft_strchr(lst->value, '$') && !ft_strchr(lst->value, '\"') && !ft_strchr(lst->value, '\''))
        return ;
    new_value = ft_malloc(total_len, ALLOC);
    while (lst->value[index])
    {
        if (lst->value[index] == '\'' || lst->value[index] == '\"')
        {
            if (lst->value[index] == '\'')
            {
                if (in_single_quote == false)
                    in_single_quote = true;
                else
                    in_single_quote = false;
            }
            index++;
        }
        else if (lst->value[index] == '$' && in_single_quote == false)
            ft_get_env(new_value, lst, &r, &index);
        else
        {
            new_value[r] = lst->value[index];
            r++;
            index++;
        }
    }
    new_value[r] = '\0';
    free(lst->value);
    lst->value = new_value;
}

void     ft_expand(t_token *lst)
{
    t_token *tmp;

    tmp = lst;
    while (tmp)
    {
        if (tmp->type == WORD || tmp->type == DOUBLEQ || tmp->type == SINGLEQ)
        {
			ft_expand_value(tmp);
            tmp->type = WORD;
        }
        tmp = tmp->next;
    }
}
