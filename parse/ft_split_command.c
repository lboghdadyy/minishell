/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:19:49 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/22 13:46:02 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokentype	ft_token_type(char *string)
{
	if (!string)
		return (WORD);
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

t_token	*ft_split_command(char **command)
{
	t_token	*lst;
	t_token	*tmp;
	int		index;
	int		delemter;

	(1) && (delemter = 0, lst = NULL, tmp = NULL, index = 0);
	if (!command || !*command)
		return (NULL);
	while (command[index])
	{
		tmp = ft_lstnew(ft_token_type(command[index]), command[index]);
		if (!tmp)
			ft_malloc(0, CLEAR);
		if (tmp->type == HERDOC)
			delemter = 1;
		else if (delemter)
		{
			tmp->type = DELEMTER;
			delemter = 0;
		}
		ft_lstadd_back(&lst, tmp);
		index++;
	}
	return (lst);
}
