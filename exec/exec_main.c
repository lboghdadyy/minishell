/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:32:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/29 21:54:17 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_execve(t_exec *head, t_env *env)
{
	char		**envp;
	struct stat	sb;

	envp = convert_t_env(env);
	execve(head->cmd, head->opt, envp);
	if (stat(head->cmd, &sb) == -1)
	{
		perror("stat");
		ft_malloc(0, CLEAR);
		exit(errno);
	}
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(head->cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		ft_malloc(0, CLEAR);
		exit(126);
	}
	perror(head->cmd);
	ft_malloc(0, CLEAR);
	exit(errno);
}

char	*search_cmd_in_path(char **arr, char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (arr[i] && !is_empty(cmd))
	{
		tmp = strj(arr[i], "/");
		tmp = strj(tmp, cmd);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char *path)
{
	char	**arr;
	char	*tmp;

	if (!cmd)
		exit(e_status(0, 0));
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (cmd_not_found(cmd), NULL);
	}
	arr = ft_split_exec(path, ':');
	if (!arr)
		return (NULL);
	tmp = search_cmd_in_path(arr, cmd);
	if (tmp)
		return (tmp);
	tmp = getcwd(NULL, 0);
	path = tmp;
	tmp = strj(tmp, "/");
	free(path);
	tmp = strj(tmp, cmd);
	if (access(tmp, F_OK | X_OK) == 0 && !is_empty(cmd))
		return (tmp);
	return (cmd_not_found(cmd), NULL);
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
			perror("fork"), ft_malloc(0, CLEAR), 1);
	if (pid == 0)
	{
		signal(SIGQUIT, handl_sig);
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
		return (perror("dup()"), ft_malloc(0, CLEAR), 1);
	while (exec)
	{
		if (!exec->flag)
			execute_cmd(exec, env);
		exec = exec->next;
	}
	dup2(fd, 0);
	close(fd);
	return (check_exit_status());
}
