#include "../../minishell.h"

t_var	*last_var(t_var *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_var_back(t_var **lst, t_var *elt)
{
	t_var	*last;

	if (!elt)
		return ;
	if (!*lst)
	{
		*lst = elt;
		return ;
	}
	last = last_var(*lst);
	last->next = elt;
}

t_var	*new_var(char *value, t_vartype type)
{
	t_var	*elt;

	elt = ft_malloc(sizeof(t_var), ALLOC);
	elt->next = NULL;
	elt->type = type;
	elt->value = value;
	return (elt);
}

t_var	*split_var(char *s)
{
	int		i;
	int		b;
	int		sub_len;
	t_var	*lst;
	t_var	*tmp;

	i = 0;
	lst = NULL;
	while (s[i])
	{
		(1) && (b = i, sub_len = skip_tillvar(s, i));
		tmp = new_var(subs(s, b, sub_len), WORD_V);
		i += sub_len;
		if (tmp->value)
			add_var_back(&lst, tmp);
		if (!s[i])
			break;
		tmp = new_var(subs(s, i, skip_variable(s, i)), VAR);
		add_var_back(&lst, tmp);
		i += skip_variable(s, i);
	}
	return (lst);
}
