/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:32:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/16 19:28:28 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_execve(t_exec *head, t_env *env)
{
	char	**envp;

	envp = convert_t_env(env);
	execve(head->cmd, head->opt, envp);
	perror("execve()");
	ft_malloc(0, CLEAR);
	exit(errno);
}

int	is_empty(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (1);
	while (s[i] && ft_is_space(s[i]))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

char	*get_cmd_path(char *cmd, char *path)
{
	char	**arr;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		cmd_not_found(cmd);
		return (NULL);
	}
	arr = ft_split_exec(path, ':');
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i] && !is_empty(cmd))
	{
		tmp = ft_strjoin(arr[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		i++;
	}
	cmd_not_found(cmd);
	return (NULL);
}

int	execute_cmd(t_exec *head, t_env **env)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		return (perror("pipe"), ft_malloc(0, CLEAR), 1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), \
			perror("fork"), ft_malloc(0, CLEAR), 0);
	if (pid == 0)
	{	
		if (is_builtin(head->cmd))
		{
			setup_child(fd, NULL, head, 1);
			execute_builtin(head, env, true);
			exit(0);
		}
		else
		{
			setup_child(fd, find_env(*env, "PATH"), head, 0);
			call_execve(head, *env);
		}
	}
	(pid) && (parent_thing(fd, head));
	return (1);
}

int	execution(t_exec *exec, t_env **env)
{
	int	fd;

	if (ft_lstsize(exec) == 1 && is_builtin(exec->cmd))
		return (execute_builtin(exec, env, false), 1);
	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (perror("dup()"), ft_malloc(0, CLEAR), 0);
	while (exec)
	{
		execute_cmd(exec, env);
		exec = exec->next;
	}
	dup2(fd, 0);
	close(fd);
	return (check_exit_status());
}
