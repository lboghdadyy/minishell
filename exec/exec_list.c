/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 03:48:22 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/18 14:45:41 by oufarah          ###   ########.fr       */
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

t_env	*ft_lstnew_exec(char *key, char *value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), ALLOC);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*ft_lstlast_exec(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
