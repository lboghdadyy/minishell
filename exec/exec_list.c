/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 03:48:22 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/16 06:41:42 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_exec	*new_node(void)
{
	t_exec	*ret;

	ret = ft_malloc(sizeof(t_exec), ALLOC);
	ret->fd_in = 0;
	ret->fd_out = 1;
	ret->cmd = NULL;
	ret->opt = NULL;
	ret->next = NULL;
	return (ret);
}

void	add_back(t_exec **head, t_exec *new)
{
	t_exec	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
