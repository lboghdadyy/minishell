/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:23:56 by oufarah           #+#    #+#             */
/*   Updated: 2025/06/13 16:14:24 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_until_pipe(t_token *lst)
{
	int	count;

	count = 0;
	while (lst && lst->type != PIPE)
	{
		if (lst->type == WORD)
			count++;
		lst = lst->next;
	}
	return (count);
}

void	handle_word(t_token *lst, t_exec *node, int *i)
{
	node->opt[*i] = ft_strdup(lst->value);
	if (*i == 0)
		node->cmd = node->opt[0];
	(*i)++;
}

int	handle_redirects(t_token **lst, t_exec *node)
{
	int	status;

	status = 0;
	if ((*lst)->type == HERDOC)
	{
		if ((*lst)->fd_reder == -1)
			status = 1;
		else
		{
			if (node->fd_in != -1)
				close (node->fd_in);
			node->fd_in = (*lst)->fd_reder;
		}
	}
	else if ((*lst)->type == R_IN)
		status = handle_redirect_in(lst, node);
	else if ((*lst)->type == APPEND)
		status = handle_append(lst, node);
	else if ((*lst)->type == R_OUT)
		status = handle_redirect_out(lst, node);
	if (status && status != 33)
		e_status(1, 1);
	return (status);
}

int	fill_node(t_token **lst, t_exec *node)
{
	int		i;
	int		ac;

	(1) && (i = 0, ac = count_until_pipe(*lst));
	node->opt = ft_malloc(sizeof(char *) * (ac + 1), ALLOC);
	while (*lst && (*lst)->type != PIPE)
	{
		if ((*lst)->type == WORD)
			handle_word(*lst, node, &i);
		else if ((*lst)->type == HERDOC)
		{
			if ((*lst)->fd_reder == -1)
				node->flag = 1;
			node->fd_in = (*lst)->fd_reder;
		}
		else
		{
			if (handle_redirects(lst, node))
				node->flag = 1;
		}
		if (*lst && (*lst)->type != PIPE)
			*lst = (*lst)->next;
	}
	node->opt[i] = NULL;
	return (0);
}

t_exec	*convert_token_to_exec(t_token *lst, t_env *env)
{
	t_exec	*head;
	t_exec	*node;
	t_token	*tmp;

	tmp = lst;
	head = NULL;
	while (lst)
	{
		node = new_node();
		fill_node(&lst, node);
		add_back(&head, node);
		if (lst && lst->type == PIPE)
			lst = lst->next;
	}
	if (ft_stop_redirect(tmp, env))
		return (NULL);
	return (head);
}
