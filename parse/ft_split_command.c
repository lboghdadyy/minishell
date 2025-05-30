/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:19:49 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/22 13:46:02 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_var(char	*s)
{
	int	index;

	index = 0;
	while (s[index])
	{
		if (s[index] == '$' && s[index + 1] && id_check(s + index + 1))
			return (1);
		index++;
	}
	return (0);
}

t_tokentype	ft_token_type(char *string)
{
	if (!string)
		return (WORD);
	if (ft_check_var(string))
		return (EXPAN);
	if (ft_check_pip(string))
		return (PIPE);
	if (ft_check_redirect_in(string))
		return (R_IN);
	if (ft_check_redirect_out(string))
		return (R_OUT);
	if (ft_check_append(string))
		return (APPEND);
	if (ft_check_heredoc(string))
		return (HERDOC);
	if (ft_check_quotes_type(string) == SINGLE)
		return (SINGLEQ);
	if (ft_check_quotes_type(string) == COUPLE)
		return (DOUBLEQ);
	return (WORD);
}

t_token	*s_cmd(char **command, t_env *envp)
{
	t_token	*lst;
	int		index;

	(void)envp;
	lst = NULL;
	index = 0;
	if (!command || !*command)
		return (NULL);
	while (command[index])
	{
		ft_lstnew(&lst, ft_token_type(command[index]), envp, command[index]);
		index++;
	}
	return (lst);
}
