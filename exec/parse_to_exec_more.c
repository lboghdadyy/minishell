/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:33:02 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/24 20:21:49 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ambigous_red(void)
{
	ft_putstr_fd("minishell : ambiguous redirect\n", 2);
	store_exit_status(1, 1);
}

int	handle_heredoc(t_token **lst, t_exec *node, t_env *env)
{
	char	*f_adress;
	int		fd_out;
	int		fd_in;
	int		status;
	int		pid;

	if (!(*lst)->next)
		return (ambigous_red(), 1);
	status = 0;
	f_adress = ft_malloc(100, ALLOC);
	f_adress = ft_strj("/tmp/", ft_itoa(((long)&fd_in)));
	fd_out = open(f_adress, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd_out), 1);
	else if (pid == 0)
	{
		if (node->fd_in != 0)
			close(node->fd_in);
		signal(SIGINT, SIG_DFL);
		ft_handle_heredoc(*lst, env, fd_out);
	}
	else
		waitpid(pid, &status, 0);
	signal(SIGINT, &handler);
	rl_replace_line("", 0);
	if (WIFSIGNALED(status))
		return (store_exit_status(130, 1), 1);
	node->fd_in = open(f_adress, O_RDONLY);
	if (node->fd_in == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
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
