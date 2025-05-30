/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:33:02 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/30 17:18:26 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_heredoc_ctx(t_heredoc_ctx *ctx)
{
	ctx->f = ft_malloc(100, ALLOC);
	if (!ctx->f)
		return (1);
	ctx->st = 0;
	ctx->fd_in = -1;
	ctx->fd_out = -1;
	ctx->pid = -1;
	ctx->f = strj("/tmp/", ft_itoa((long)&ctx->fd_in));
	ctx->fd_out = open(ctx->f, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (ctx->fd_out == -1)
		return (perror("open"), 1);
	ctx->pid = fork();
	if (ctx->pid < 0)
		return (perror("fork"), close(ctx->fd_out), 1);
	return (0);
}

int	handle_heredoc(t_token **lst, t_exec *node, t_env *env)
{
	t_heredoc_ctx	ctx;

	if (!(*lst)->next)
		return (ambigous_red(), 1);
	if (init_heredoc_ctx(&ctx))
		return (1);
	else if (ctx.pid == 0)
	{
		if (node->fd_in != 0)
			close(node->fd_in);
		signal(SIGINT, SIG_DFL);
		ft_handle_heredoc(*lst, env, ctx.fd_out);
	}
	else
		waitpid(ctx.pid, &ctx.st, 0);
	signal(SIGINT, &handler);
	node->fd_in = open(ctx.f, O_RDONLY);
	if (node->fd_in == -1 || WIFSIGNALED(ctx.st))
	{
		while ((*lst)->next && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
		if (WTERMSIG(ctx.st) == SIGINT)
			return (e_status(130, 1), 1);
		else
			perror("minishell");
	}
	return (0);
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
		while ((*lst)->next && (*lst)->next->type != PIPE)
			(*lst) = (*lst)->next;
		return (1);
	}
	else
	{
		if ((*lst)->next)
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
		while ((*lst)->next && (*lst)->next->type != PIPE)
			(*lst) = (*lst)->next;
		return (1);
	}
	else
	{
		if ((*lst)->next)
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
		while ((*lst)->next && (*lst)->next->type != PIPE)
			(*lst) = (*lst)->next;
		return (1);
	}
	else
	{
		if ((*lst)->next)
			(*lst) = (*lst)->next;
	}
	return (0);
}
