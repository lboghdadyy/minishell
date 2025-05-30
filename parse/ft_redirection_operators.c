/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_operators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:04:39 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/30 19:04:59 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_herdoc(char *v, t_env *envp)
{
	char	*n_v;
	int		i;
	bool	reset;
	int		b_i;
	char	*s;

	(1) && (n_v = NULL, i = 0, reset = true);
	while (v[i])
	{
		if (reset)
			(1) && (b_i = i, reset = false);
		if (v[i] == '$' && v[i + 1] && !ft_strchr(". ", v[i + 1]))
		{
			(1) && (s = subs(v, b_i, i - b_i), n_v = strj(n_v, s));
			s = g_env(v, &i, envp);
			n_v = strj(n_v, s);
			reset = true;
		}
		else if (!v[i + 1])
			(1) && (i++, s = subs(v, b_i, i - b_i), \
			n_v = strj(n_v, s));
		else
			i++;
	}
	return (n_v);
}

int	ft_handle_heredoc(t_token *lst, t_env *env, int fd_out)
{
	char	*input;
	char	*expanded;

	if (fd_out == -1)
		return (1);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, lst->next->value))
			break ;
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
	exit(0);
	return (1);
}
