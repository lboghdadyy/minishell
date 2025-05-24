/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:55:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/24 21:57:57 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc_fork(t_token *lst, t_exec *node, t_env *env, int fd_out)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd_out), 1);
	else if (pid == 0)
	{
		if (node->fd_in != 0)
			close(node->fd_in);
		signal(SIGINT, SIG_DFL);
		ft_handle_heredoc(lst, env, fd_out);
	}
	else
		waitpid(pid, &status, 0);
	signal(SIGINT, &handler);
	rl_replace_line("", 0);
	if (WIFSIGNALED(status))
		return (store_exit_status(130, 1), 1);
	return (0);
}

int	handle_heredoc(t_token **lst, t_exec *node, t_env *env)
{
	char	*f_adress;
	int		fd_out;

	if (!(*lst)->next)
		return (ambigous_red(), 1);
	f_adress = ft_malloc(100, ALLOC);
	f_adress = ft_strj("/tmp/", ft_itoa(((long)&fd_out)));
	fd_out = open(f_adress, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (handle_heredoc_fork(*lst, node, env, fd_out))
		return (1);
	node->fd_in = open(f_adress, O_RDONLY);
	if (node->fd_in == -1)
	{
		perror("minishell");
		while ((*lst) && (*lst)->type != PIPE)
			(*lst) = (*lst)->next;
	}
	return (0);
}
