/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:23:56 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/18 21:54:53 by sbaghdad         ###   ########.fr       */
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

void	handle_redirects(t_token **lst, t_exec *node, t_env *env)
{
	if ((*lst)->type == HERDOC)
		handle_heredoc(lst, node, env);
	else if ((*lst)->type == REDIRECT_IN)
		handle_redirect_in(lst, node);
	else if ((*lst)->type == APPEND)
		handle_append(lst, node);
	else if ((*lst)->type == REDIRECT_OUT)
		handle_redirect_out(lst, node);
	if (*lst && (*lst)->type != WORD)
		*lst = (*lst)->next;
}

void	fill_node(t_token **lst, t_exec *node, t_env *env)
{
	int	i;
	int	ac;

	i = 0;
	ac = count_until_pipe(*lst);
	node->opt = ft_malloc(sizeof(char *) * (ac + 1), ALLOC);
	while (*lst && (*lst)->type != PIPE)
	{
		if ((*lst)->type == WORD)
			handle_word(*lst, node, &i);
		else
			handle_redirects(lst, node, env);
		if (*lst)
			*lst = (*lst)->next;
	}
	node->opt[i] = NULL;
}

t_exec	*convert_token_to_exec(t_token *lst, t_env *env)
{
	t_exec	*head;
	t_exec	*node;

	head = NULL;
	while (lst)
	{
		node = new_node();
		fill_node(&lst, node, env);
		add_back(&head, node);
		if (lst && lst->type == PIPE)
			lst = lst->next;
	}
	return (head);
}
