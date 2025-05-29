/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:23:56 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/29 13:07:38 by sbaghdad         ###   ########.fr       */
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

int	handle_redirects(t_token **lst, t_exec *node, t_env *env)
{
	int	status;

	status = 0;
	if ((*lst)->type == HERDOC)
		status = handle_heredoc(lst, node, env);
	else if ((*lst)->type == R_IN)
		status = handle_redirect_in(lst, node);
	else if ((*lst)->type == APPEND)
		status = handle_append(lst, node);
	else if ((*lst)->type == R_OUT)
		status = handle_redirect_out(lst, node);
	if (*lst && (*lst)->type != WORD)
		*lst = (*lst)->next;
	if (status)
		e_status(1, 1);
	return (status);
}

int	fill_node(t_token **lst, t_exec *node, t_env *env)
{
	int		i;
	int		ac;
	t_token	*tmp;

	i = 0;
	tmp = *lst;
	ac = count_until_pipe(*lst);
	node->opt = ft_malloc(sizeof(char *) * (ac + 1), ALLOC);
	while (*lst && (*lst)->type != PIPE)
	{
		if ((*lst)->type == WORD)
			handle_word(*lst, node, &i);
		else
		{
			if (handle_redirects(lst, node, env))
				node->flag = 1;
		}
		if (*lst)
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
		fill_node(&lst, node, env);
		add_back(&head, node);
		if (lst && lst->type == PIPE)
			lst = lst->next;
	}
	if (ft_stop_redirect(tmp, env))
		return (NULL);
	return (head);
}
