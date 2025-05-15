#include "../minishell.h"

char    *ft_expand_herdoc(char    *value, t_env *envp)
{
    char    *new_value = NULL;
    int     index = 0;
    bool    reset = true;
    int     back_to_index;
    char    *sub;

    while (value[index])
    {
        if (reset)
        {
            back_to_index = index;
            reset = false;
        }
        if (value[index] == '$' && value[index + 1] && !ft_strchr(". ", value[index + 1]))
        {
            sub = ft_substr(value, back_to_index, index - back_to_index);
            new_value = ft_strjoin(new_value, sub);
            sub = ft_get_env(value, &index, envp);
            new_value = ft_strjoin(new_value, sub);
            reset = true;
        }
        else if (!value[index + 1])
        {
            index++;
            sub = ft_substr(value, back_to_index, index - back_to_index);
            new_value = ft_strjoin(new_value, sub);
        }
        else
            index++;
    }
    return (new_value);
}

int	ft_handle_heredoc(t_token *lst, t_env *env)
{
	t_token	*tmp = lst;
	char	*input;
    char    *expanded;
	int		fd[2];

	
    if (pipe(fd) == -1)
        return (-1);
    while (1)
    {
        input = readline("> ");
        if (!input || strcmp(input, tmp->next->value) == 0)
        {
            free(input);
            break;
        }
        if (ft_strchr(input, '$'))
        {
            expanded = ft_expand_herdoc(input, env);
            if (expanded)
            {
                write(fd[1], expanded, strlen(expanded));
                write(fd[1], "\n", 1);
            }
        }
        else
        {
            write(fd[1], input, strlen(input));
            write(fd[1], "\n", 1);
        }
        free(input);
    }
    close(fd[1]);
    return fd[0];
}

