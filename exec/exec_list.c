/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 03:48:22 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/21 16:03:17 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_env(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
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

void	ft_lstadd_back_exec(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_exec(*lst)->next = new;
}
