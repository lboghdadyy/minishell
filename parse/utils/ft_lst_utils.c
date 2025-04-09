#include "../../minishell.h"

t_list	*ft_lstnew()
{
	t_list		*elt;

	elt = malloc(sizeof(t_list));
	if (!elt)
		return (NULL);
	// elt->command = command;
	// elt->flags = flags;
	// elt->operator = c;
	elt->next = NULL;
	return (elt);
}


t_list	*ft_lstlast(t_list *lst)
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

void	ft_lstadd_back(t_list**lst, t_list*new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
}
