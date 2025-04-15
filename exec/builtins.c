/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:27:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/15 06:23:47 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		return (1);
	else if (ft_strcmp(cmd, "cd"))
		return (1);
	else if (ft_strcmp(cmd, "pwd"))
		return (1);
	else if (ft_strcmp(cmd, "export"))
		return (1);
	else if (ft_strcmp(cmd, "unset"))
		return (1);
	else if (ft_strcmp(cmd, "env"))
		return (1);
	else if (ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

// void	ft_echo(t_exec *exec)
// {

// }

void	execute_builtin(t_exec *exec)
{
	if (ft_strcmp(exec->cmd, "echo"))
		ft_echo(exec);
	else if (ft_strcmp(exec->cmd, "cd"))
		ft_cd();
	else if (ft_strcmp(exec->cmd, "pwd"))
		ft_pwd();
	else if (ft_strcmp(exec->cmd, "export"))
		ft_export();
	else if (ft_strcmp(exec->cmd, "unset"))
		ft_unset();
	else if (ft_strcmp(exec->cmd, "env"))
		ft_env();
	else if (ft_strcmp(exec->cmd, "exit"))
		ft_exit();
}

