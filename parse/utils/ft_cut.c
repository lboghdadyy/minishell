/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:50:22 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/27 12:52:27 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*cut_till_pip(t_token *lst, int pip)
{
	t_token	*new_lst;
	int		index;

	(1) && (new_lst = lst, index = 0);
	while (lst)
	{
		if (index == pip)
		{
			while (lst && lst->type != PIPE)
			{
				del_token_node(&new_lst, lst);
				lst = lst->next;
			}
			if (lst && lst->type == PIPE)
			{
				del_token_node(&new_lst, lst);
				(1) && (lst = lst->next, index++);
			}
			continue ;
		}
		if (lst->type == PIPE)
			index++;
		lst = lst->next;
	}
	return (new_lst);
}

int	check_red_in(t_token *lst)
{
	int	fd;

	fd = -2;
	if (lst->next)
		fd = open(lst->next->value, O_RDONLY);
	if (!lst->next || fd == -1)
	{
		if (fd == -1)
			perror("minishell");
		if (!lst->next)
			ambigous_red();
		return (e_status(1, 1), 1);
	}
	unlink(lst->next->value);
	close(fd);
	return (0);
}

int	check_red_out(t_token *lst)
{
	int	fd;

	fd = -2;
	if (lst->next)
		fd = open(lst->next->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!lst->next || fd == -1)
	{
		if (fd == -1)
			perror("minishell");
		if (!lst->next)
			ambigous_red();
		return (e_status(1, 1), 1);
	}
	unlink(lst->next->value);
	close(fd);
	return (0);
}

int	check_appand(t_token *lst)
{
	int	fd;

	fd = -2;
	if (lst->next)
		fd = open(lst->next->value, \
	O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!lst->next || fd == -1)
	{
		if (fd == -1)
			perror("minishell");
		if (!lst->next)
			ambigous_red();
		return (e_status(1, 1), 1);
	}
	unlink(lst->next->value);
	close(fd);
	return (0);
}

void	cut_lst(t_token **lst)
{
	t_cut	c;

	(1) && (c.pip_i = 0, c.tmp = *lst);
	while (c.tmp)
	{
		if (c.tmp->type == PIPE)
			c.pip_i++;
		if (c.tmp->type == R_IN)
		{
			if (check_red_in(c.tmp))
				(1) && (*lst = cut_till_pip(*lst, c.pip_i), c.tmp = *lst);
		}
		else if (c.tmp->type == R_OUT)
		{
			if (check_red_out(c.tmp))
				(1) && (*lst = cut_till_pip(*lst, c.pip_i), c.tmp = *lst);
		}
		else if (c.tmp->type == APPEND)
		{
			if (check_appand(c.tmp))
				(1) && (*lst = cut_till_pip(*lst, c.pip_i), c.tmp = *lst);
		}
		if (c.tmp)
			c.tmp = c.tmp->next;
	}
}
