/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:27:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/18 09:45:44 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env)
{
	while (*env)
	{
		if (ft_strchr(*env, '='))
		{
			ft_putstr_fd(*env, 1);
			ft_putstr_fd("\n", 1);
		}
		env++;
	}
	return (0);
}

int	is_valid_option(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	int	nline;
	int	i;

	i = 1;
	nline = 0;
	while (cmd[i] && is_valid_option(cmd[i]))
	{
		nline = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!nline)
		write(1, "\n", 1);
	return (0);
}

int	ft_pwd(void)
{
	char	*a;

	a = getcwd(NULL, 0);
	if (a)
	{
		ft_putstr_fd(a, 1);
		ft_putstr_fd("\n", 1);
		free(a);
		return (0);
	}
	// perror("pwd :"); error handling
	return (1);
}

int	ft_export(char **opt, char **env)
{
	(void)opt;
	(void)env;
	return 0;
}
int ft_unset(char **opt, char **env)
{
	(void)opt;
	(void)env;
	return 0;
}
int ft_cd(char **opt, char **env)
{
	(void)opt;
	(void)env;
	return 0;
}
int	ft_exec_exit(char **opt)
{
	(void)opt;
	return 0;
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_exec *exec, char **env)
{
	if (!ft_strcmp(exec->cmd, "echo"))
		ft_echo(exec->opt);
	else if (!ft_strcmp(exec->cmd, "cd"))
		ft_cd(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(exec->cmd, "export"))
		ft_export(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "unset"))
		ft_unset(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "env"))
		ft_env(env);
	else if (!ft_strcmp(exec->cmd, "exit"))
		ft_exec_exit(exec->opt);
}
