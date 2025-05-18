/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:33:02 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/17 16:41:25 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_token **lst, t_exec *node, t_env *env)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = ft_handle_heredoc(*lst, env);
}

void	handle_redirect_in(t_token **lst, t_exec *node)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = open((*lst)->next->value, O_RDONLY);
}

void	handle_append(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	node->fd_out = open((*lst)->next->value, \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	handle_redirect_out(t_token **lst, t_exec *node)
{
	if (node->fd_out != 1)
		close(node->fd_out);
	node->fd_out = open((*lst)->next->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
}
