#include "../minishell.h"

int skip_variable(char *value, int index)
{
    int count;

    count = index;
    count++;
    if (value[count] == '$')
        return 2;
    while (value[count] && !ft_strchr("\" $.", value[count]))
        count++;
    return (count - index);
}

size_t  ft_len_wo_quotes(char *value)
{
    size_t count;
    int     i;

    i = 0;
    count = 0;
    while (value[i])
    {
		if (!ft_strchr("\'\"", value[i]))
			count++;
		i++;
	}
    return (count);
}

char	*ft_get_env(t_token *lst, int *index)
{
	char	*sub;
	char	*found;
	size_t	skipped;

	skipped = skip_variable(lst->value, *index);
    sub = ft_substr(lst->value, *index + 1, skipped - 1);
	*index += skipped;
	found = getenv(sub);
	free(sub);
	return (found);
}

void    ft_remove_quotes(t_token *tmp)
{
    int     index = 0;
    char    *clean;
    int     index_tmp = 0;

    clean = ft_malloc(ft_len_wo_quotes(tmp->value) + 1, ALLOC);
    while (tmp->value[index_tmp])
    {
        if (tmp->value[index_tmp] != '\'' && tmp->value[index_tmp] != '\"')
        {
            clean[index] = tmp->value[index_tmp];
            index++;
        }
        index_tmp++;
    }
    free(tmp->value);
    tmp->value = clean;
}

void    ft_expand_value(t_token *lst)
{
    char    *new_value = NULL;
    int     index = 0;
    int     back_to_index;
    int    SINGLEQ = 0;
    char    *sub;

    while (lst->value[index])
    {
        back_to_index = index;
        while (lst->value[index] && lst->value[index] != '$')
        {
            if (lst->value[index] == '\'')
                SINGLEQ++;
            index++;
        }
        sub = ft_substr(lst->value, back_to_index, index - back_to_index);
        new_value = ft_strjoin(new_value, sub);
        if (lst->value[index] == '$' && SINGLEQ % 2 == 0)
        {
            sub = ft_get_env(lst, &index);
            new_value = ft_strjoin(new_value, sub);
        }
    }
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
            if (ft_strchr(tmp->value, '$'))
			    ft_expand_value(tmp);
            ft_remove_quotes(tmp);
            tmp->type = WORD;
        }
        tmp = tmp->next;
    }
}
