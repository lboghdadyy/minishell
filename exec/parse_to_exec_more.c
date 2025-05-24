/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:33:02 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/24 21:54:58 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ambigous_red(void)
{
	ft_putstr_fd("minishell : ambiguous redirect\n", 2);
	store_exit_status(1, 1);
}

int	handle_redirect_in(t_token **lst, t_exec *node)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	if (!(*lst)->next)
	{
		ambigous_red();
		return (1);
	}
	node->fd_in = open((*lst)->next->value, O_RDONLY);
	if (node->fd_in == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
	return (0);
}

int	handle_append(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	if (!(*lst)->next)
	{
		ambigous_red();
		return (1);
	}
	node->fd_out = open((*lst)->next->value, \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
	return (0);
}

int	handle_redirect_out(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	if (!(*lst)->next)
	{
		ambigous_red();
		return (1);
	}
	node->fd_out = open((*lst)->next->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (node->fd_out == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
	return (0);
}
