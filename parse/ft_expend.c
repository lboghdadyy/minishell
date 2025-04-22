#include "../minishell.h"

int skip_variable(char *value, int index)
{
    int count;

    count = index + 1;
    if (value[count] == '$')
        return 2;
    while (value[count] && !ft_strchr("\"\' $.+", value[count]))
        count++;
    return (count - index);
}

size_t  ft_len_wo_quotes(char *value)
{
    size_t      count;
    size_t     i;
    size_t      count_inside;
    char        c;

    i = 0;
    count = 0;
    if (!value)
        return (0);
    while (value[i])
    {
        if (value[i] == '\'' || value[i] == '\"')
        {
            c = value[i];
            count_inside = 0;
            i++;
            while (value[i] && value[i] != c)
            {
                count_inside++;
                i++;
            }
            if (value[i] == c)
                i++;
			count += count_inside;
        }
		else
        {
            count++;
            i++;
        }
	}
    return (count);
}

char	*ft_get_env(t_token *lst, int *index, t_env *envp)
{
	char	*sub;
	char	*found;
	size_t	skipped;
    t_env   *tmp;

	skipped = skip_variable(lst->value, *index);
    sub = ft_substr(lst->value, *index + 1, skipped - 1);
	*index += skipped;
	tmp = find_env(envp, sub);
    if (!tmp)
        return (NULL);
    found = tmp->value;
	return (found);
}

void    ft_remove_quotes(t_token *tmp)
{
    int     index = 0;
    char    *clean;
    int     index_tmp = 0;
    bool    single_quots = false;
    bool    double_quots = false;
    
    if (!tmp->value)
    {
        tmp->value = ft_strdup("");
        return ;
    }
    clean = ft_malloc(ft_len_wo_quotes(tmp->value) + 1, ALLOC);
    while (tmp->value[index_tmp])
    {
        if (tmp->value[index_tmp] == '\'' && !double_quots)
        {
            single_quots = !single_quots;
            index_tmp++;
        }
        else if (tmp->value[index_tmp] == '\"' && !single_quots)
        {
            double_quots = !double_quots;
            index_tmp++;
        }
        else
        {
            clean[index] = tmp->value[index_tmp];
            index_tmp++;
            index++;
        }
    }
    clean[index] = '\0';
    tmp->value = clean;
}

// void    ft_extract(char *new_value, char *value, int index, int back_to_index)
// {
//     char    *sub;

//     sub = ft_substr(lst->value, back_to_index, index - back_to_index);
//     new_value = ft_strjoin(new_value, sub);
// }

void    ft_expand_value(t_token *lst, t_env *envp)
{
    char    *new_value = NULL;
    int     index = 0;
    bool    reset = true;
    int     back_to_index;
    bool    single_quots = false;
    char    *sub;

    while (lst->value[index])
    {
        if (reset)
        {
            back_to_index = index;
            reset = false;
        }
        if (lst->value[index] == '$' && !single_quots && lst->value[index + 1] && !ft_strchr(". ", lst->value[index + 1]))
        {
            sub = ft_substr(lst->value, back_to_index, index - back_to_index);
            new_value = ft_strjoin(new_value, sub);
            sub = ft_get_env(lst, &index, envp);
            new_value = ft_strjoin(new_value, sub);
            reset = true;
        }
        else if (!lst->value[index + 1])
        {
            sub = ft_substr(lst->value, back_to_index, index - back_to_index);
            new_value = ft_strjoin(new_value, sub);
            index++;
        }
        else if (lst->value[index] == '\'')
        {
            single_quots = !single_quots;
            index++;
        }
        else
            index++;
    }
    lst->value = new_value;
}

bool    check_vars(char *value)
{
    int index = 0;

    while (value[index])
    {
        if (value[index] == '$' && (value[index + 1] && !ft_strchr("\" .", value[index + 1])))
            return (true);
        index++;
    }
    return (false);
}

void     ft_expand(t_token *lst, t_env *envp)
{
    t_token *tmp;

    tmp = lst;
    while (tmp)
    {
        if (ft_strchr(tmp->value, '$'))
        {
            if (check_vars(tmp->value))
                ft_expand_value(tmp, envp);
        }
        if (tmp->type == SINGLEQ || tmp->type == DOUBLEQ)
        {
            ft_remove_quotes(tmp);
            tmp->type = WORD;
        }
        tmp = tmp->next;
    }

}
