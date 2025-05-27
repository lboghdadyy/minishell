/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:14:28 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/27 12:52:39 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*ft_lstnew(t_tokentype type, char *value)
{
	t_token		*elt;

	elt = ft_malloc(sizeof(t_token), ALLOC);
	elt->type = type;
	elt->value = value;
	elt->next = NULL;
	elt->previous = NULL;
	elt->fd_reder = -1;
	return (elt);
}

void	del_token_node(t_token **head, t_token *node_to_delete)
{
	if (!head || !*head || !node_to_delete)
		return ;
	if (node_to_delete->previous)
		node_to_delete->previous->next = node_to_delete->next;
	else
		*head = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->previous = node_to_delete->previous;
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	new->previous = tmp;
}
