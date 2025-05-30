/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:14:28 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/30 16:34:45 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_split_ex(t_token **lst, t_env *e, char *value)
{
	t_token		*elt;
	char		*exp;
	char		**l;
	int			i;

	(1) && (i = 0, elt = NULL, exp = exp_val(value, e, 0));
	if (ft_strchr(exp, '$') || !check_for_s(exp))
	{
		elt = ft_malloc(sizeof(t_token), ALLOC);
		elt->type = WORD;
		elt->value = value;
		elt->next = NULL;
		elt->previous = NULL;
		return (ft_lstadd_back(lst, elt));
	}
	if (check_for_s(exp))
	{
		l = ft_split(exp);
		if (!l || !*l)
			return ;
		while (l[i])
			ft_lstnew(lst, WORD, e, l[i++]);
	}
}

void	ft_lstnew(t_token **lst, t_tokentype type, t_env *e, char *value)
{
	t_token		*elt;
	t_token		*last;

	elt = ft_malloc(sizeof(t_token), ALLOC);
	elt->value = value;
	elt->next = NULL;
	elt->previous = NULL;
	elt->fd_reder = -1;
	last = ft_lstlast(*lst);
	if (last && last->type == HERDOC)
		type = DELEMTER;
	if (type == EXPAN)
	{
		ft_split_ex(lst, e, value);
		return ;
	}
	if (type == DOUBLEQ || type == SINGLEQ || type == DELEMTER)
	{
		elt->value = ft_remove_quotes(value);
		if (type != DELEMTER)
			elt->type = WORD;
	}
	elt->type = type;
	ft_lstadd_back(lst, elt);
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
