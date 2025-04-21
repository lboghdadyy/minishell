/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:32:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/21 11:31:07 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_until_pipe(t_token *lst)
{
	int	count;

	count = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type == WORD)
			count++;
		lst = lst->next;
	}
	return (count);
}
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

void	call_execve(t_exec *head, t_env *env)
{
	(void)env;
	execve(head->cmd, head->opt, NULL); // convert t_env *env to char **env and pass it to execve
	perror("execve()");
	ft_malloc(0, CLEAR);
	exit(errno);
}

t_exec	*convert_token_to_exec(t_token *lst)
{
	t_exec	*head;
	t_exec	*node;
	int		ac;
	int		i;

	head = NULL;
	while (lst)
	{
		node = new_node();
		ac = count_until_pipe(lst);
		node->opt = ft_malloc(sizeof(char *) * ac + 1, ALLOC);
		i = 0;
		while (lst && lst->type != PIPE)
		{
			if (lst->type == WORD || lst->type >= 6)
			{
				node->opt[i] = ft_strdup(lst->value);
				if (i == 0)
					node->cmd = node->opt[0];
				i++;
			}
			else if (lst->type == HERDOC || lst->type == REDIRECT_IN)
			{
				if (node->fd_in != 0)
					close(node->fd_in);
				node->fd_in = lst->fd_reder;
				lst = lst->next;
			}
			else if (lst->type == APPEND || lst->type == REDIRECT_OUT)
			{
				if (node->fd_out != 1)
					close(node->fd_out);
				node->fd_out = lst->fd_reder;
				lst = lst->next;
			}
			lst = lst->next;
		}
		node->opt[i] = NULL;
		add_back(&head, node);
		if (lst && lst->type == PIPE)
			lst = lst->next;
	}
	return (head);
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

int	execute_cmd(t_exec *head, t_env **env, char **envp)
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
			execute_builtin(head, env, envp);
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

int	execution(t_exec *exec, t_env **env, char **envp)
{
	int	fd;

	if (ft_lstsize(exec) == 1 && is_builtin(exec->cmd))
		return (execute_builtin(exec, env, envp), 1); // execute the builtin without forking and return
	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (perror("dup()"), ft_malloc(0, CLEAR), 0);
	while (exec)
	{
		execute_cmd(exec, env, envp);
		exec = exec->next;
	}
	dup2(fd, 0);
	close(fd);
	return (check_exit_status());
}
