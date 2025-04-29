/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:27:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/29 18:21:47 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_env *env)
{
	char	*a;
	t_env	*pwd_env;
	char	*from_cd;

	a = getcwd(NULL, 0);
	if (a)
	{
		ft_putstr_fd(a, 1);
		ft_putstr_fd("\n", 1);
		free(a);
		return (0);
	}
	else
	{
		pwd_env = find_env(env, "PWD");
		if (!pwd_env)
		{
			from_cd = ft_cd(NULL, NULL);
			if (!from_cd)
				return (perror("pwd"), 1);
			ft_putstr_fd(from_cd, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
		else
		{
			ft_putstr_fd(pwd_env->value, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	perror("pwd");
	return (1);
}

int	ft_exec_exit(char **opt)
{
	(void)opt;
	return (0);
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

void	execute_builtin(t_exec *exec, t_env **env)
{
	if (!ft_strcmp(exec->cmd, "echo"))
		ft_echo(exec->opt);
	else if (!ft_strcmp(exec->cmd, "cd"))
		ft_cd(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "pwd"))
		ft_pwd(*env);
	else if (!ft_strcmp(exec->cmd, "export"))
		ft_export(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "unset"))
		ft_unset(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "env"))
		ft_env(*env);
	else if (!ft_strcmp(exec->cmd, "exit"))
		ft_exec_exit(exec->opt);
}
