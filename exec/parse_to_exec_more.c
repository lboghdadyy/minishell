/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:33:02 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/18 21:59:27 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_token **lst, t_exec *node, t_env *env)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = ft_handle_heredoc(*lst, env);
	if (node->fd_out == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
}

void	handle_redirect_in(t_token **lst, t_exec *node)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = open((*lst)->next->value, O_RDONLY);
	if (node->fd_out == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
}

void	handle_append(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	node->fd_out = open((*lst)->next->value, \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
}

void	handle_redirect_out(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	node->fd_out = open((*lst)->next->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (node->fd_out == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
}
