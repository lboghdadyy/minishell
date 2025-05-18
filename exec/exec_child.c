/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:16:24 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/17 16:59:53 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ignore_first_cmd(int res, int get)
{
	static int	ret;

	if (!get)
		ret = res;
	return (ret);
}

int	check_exit_status(void)
{
	int	status;
	int	check;

	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			store_exit_status(WEXITSTATUS(status), 1);
		else if (WIFSIGNALED(status))
			store_exit_status(WEXITSTATUS(status) & 128, 1);
		check = status;
	}
	return (WEXITSTATUS(check));
}

void	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	ft_malloc(0, CLEAR);
	exit(127);
}

int	parent_thing(int *fd, t_exec *head)
{
	if (head->next && dup2(fd[0], 0) == -1)
		perror("dup2");
	close(fd[0]);
	close(fd[1]);
	return (1);
}

void	setup_child(int *fd, t_env *path, t_exec *head, int bltn)
{
	if (!bltn)
	{
		if (!path)
			cmd_not_found(head->cmd);
		head->cmd = get_cmd_path(head->cmd, path->value);
	}
	if (head->next)
		dup2(fd[1], 1);
	if (head->fd_in != 0)
	{
		dup2(head->fd_in, 0);
		close(head->fd_in);
	}
	if (head->fd_out != 1)
	{
		dup2(head->fd_out, 1);
		close(head->fd_out);
	}
	close(fd[1]);
	close(fd[0]);
}
