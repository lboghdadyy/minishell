/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:32:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/15 06:05:06 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_exec *exec)
{
	int	size;

	size = 0;
	while (exec)
	{
		size++;
		exec = exec->next;
	}
	return (size);
}

void	execution(t_exec *exec)
{
	if (ft_lstsize(exec) == 1 && is_builtin(exec->cmd))
		return (execute_builtin(exec)); // execute the builtin without forking and return
	while (exec)
	{
		// setup child
		if (is_builtin(exec->cmd))
			execute_builtin(exec);
		else
			execute_cmd(exec);
	}		
}
