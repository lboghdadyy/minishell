#include "../../minishell.h"

t_token	*ft_lstnew(t_tokentype type, char *value)
{
	t_token		*elt;

	elt = ft_malloc(sizeof(t_token), ALLOC);
	if (!elt)
		return (NULL);
	elt->type = type;
	elt->value = value;
	elt->next = NULL;
	return (elt);
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
}

void	ft_lstclear(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		// free(temp->value);
		// free(temp);
	}
}
