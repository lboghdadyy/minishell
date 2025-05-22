/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:04:39 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/21 17:41:00 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sig_f;

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

void	handle_sigint(int sig)
{
	(void)sig;
	exit(127);
}

int	ft_handle_heredoc(t_token *lst, t_env *env, int fd_out)
{
	char	*input;
	char	*expanded;


	sig_f = 0;
	if (fd_out == -1)
		return (1);
	while (1)
	{
		write(1, "> ", 1);
		input = get_next_line(NULL);
		if (!input || !ft_strcmp(input, lst->next->value))
			break;
		if (strchr(input, '$'))
			expanded = ft_expand_herdoc(input, env);
		else
			expanded = input;
		ft_putstr_fd(expanded, fd_out);
		write(fd_out, "\n", 1);
		free(input);
	}
	free(input);
	close(fd_out);
	exit (0);
	return (1);
}
