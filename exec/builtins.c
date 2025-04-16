/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:27:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/16 06:45:00 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **env)
{
	while (*env)
	{
		ft_putstr_fd(*env++, 1);
		ft_putstr_fd("\n", 1);
	}
}

int	ft_echo(t_exec *exec)
{
	int	nline;
	int	i;

	i = 1;
	nline = 0;
	if (ft_strcmp(exec->opt[1], "-n") && exec->opt[1])
		nline = 1;
	ft_putstr_fd(exec->opt[i], 1);
	if (!nline)
		ft_putstr_fd("\n", 1);
	return (0);
}

int		ft_cd(char **opt, char **env)
{
	return 0;
}
int		ft_pwd(void)
{
	return 0;
}
int		ft_export(char **opt, char **env)
{
	return 0;
}
int		ft_unset(char **opt, char **env)
{
	return 0;
}
int		ft_exit_exec(char **opt)
{
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

