/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad < sbaghdad@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:59:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/16 12:39:13 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage.h"

t_garbage	*ft_lstlast_garbage(t_garbage *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_to_garabage(t_garbage **lst, t_garbage *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_garbage(*lst)->next = new;
}

t_garbage	*ft_new_garbage(void *adress)
{
	t_garbage	*new;

	new = malloc (sizeof(t_garbage));
	if (!new)
	{
		free(adress);
		ft_malloc(0, CLEAR);
	}
	new->address = adress;
	new->next = NULL;
	return (new);
}

void	clear_it(t_garbage *garbage)
{
	t_garbage	*clear;

	while (garbage)
	{
		clear = garbage->next;
		free(garbage->address);
		free(garbage);
		garbage = clear;
	}
	// clear_fds(0, 0);
}

void	*ft_malloc(size_t size, int flag)
{
	static t_garbage	*garbage;
	void				*ret;

	if (flag == CLEAR)
	{
		clear_it(garbage);
		exit(size);
	}
	ret = malloc(size);
	if (!ret)
	{
		clear_it(garbage);
		exit(1);
	}
	add_to_garabage(&garbage, ft_new_garbage(ret));
	return (ret);
}
