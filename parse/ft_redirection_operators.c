#include "../minishell.h"

void	ft_handle_heredoc(t_token *lst, t_env *env)
{
	t_token	*tmp = lst;
	char	*input;
    char    *expanded;
	int		fd[2];


	while (tmp)
	{
		if (tmp->type == HERDOC)
		{
            // pipe(fd);
			if (pipe(fd) == -1)
				return ;
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
                    expanded = ft_expand_value(input, env);
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
			tmp->fd_reder = fd[0];
		}
		tmp = tmp->next;
	}
}

int    ft_redirection_operators(t_token *lst, t_env *env)
{
    t_token     *tmp;
    t_token     *tmp_2;
    bool        herdoc = false;
    int         resault;

    if (!lst)
        return (1);
    tmp = lst;
    resault = 0;
    tmp_2 = lst;
    while (tmp_2)
    {
        if (tmp_2->type == HERDOC && !herdoc)
        {
            if (!tmp_2->previous)
                resault = 1;
            herdoc = true;
        }
        tmp_2 = tmp_2->next;
    }
    if (herdoc)
        ft_handle_heredoc(lst, env);
    while(tmp)
    {
        if (tmp->type == REDIRECT_OUT)
            tmp->fd_reder = clear_fds(tmp->next->value, RED_OUT, 1);
        if (tmp->type == APPEND)
            tmp->fd_reder = clear_fds(tmp->next->value, APPE, 1);
        if (tmp->type == REDIRECT_IN)
            tmp->fd_reder = clear_fds(tmp->next->value, RED_IN, 1);
        tmp = tmp->next;
    }
    return (resault);
}