/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:23:56 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/15 16:06:16 by sbaghdad         ###   ########.fr       */
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

t_exec	*convert_token_to_exec(t_token *lst, t_env	*env)
{
	t_exec	*head;
	t_exec	*node;
	int		ac;
	int		i;

	head = NULL;
	while (lst)
	{
		node = new_node();
		ac = count_until_pipe(lst);
		node->opt = ft_malloc(sizeof(char *) * (ac + 1), ALLOC);
		i = 0;
		while (lst && lst->type != PIPE)
		{
			if (lst->type == WORD)
			{
				node->opt[i] = ft_strdup(lst->value);
				if (i == 0)
					node->cmd = node->opt[0];
				i++;
			}
			else if (lst->type == HERDOC)
			{
				if (node->fd_in != 0)
					close(node->fd_in);
				node->fd_in = ft_handle_heredoc(lst, env);
				lst = lst->next;
			}
			else if (lst->type == REDIRECT_IN)
			{
				if (node->fd_in != 0)
					close(node->fd_in);
				node->fd_in = open(lst->next->value, O_RDONLY);
			}
			else if (lst->type == APPEND)
			{
				if (node->fd_out != 1)
					close(node->fd_out);
				node->fd_out = open(lst->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				lst = lst->next;
			}
			else if (lst->type == REDIRECT_OUT)
			{
				if (node->fd_out != 1)
					close(node->fd_out);
				node->fd_out = open(lst->next->value, O_RDWR | O_CREAT, 0644);
				lst = lst->next;
			}
			lst = lst->next;
		}
		node->opt[i] = NULL;
		add_back(&head, node);
		if (lst && lst->type == PIPE)
			lst = lst->next;
	}
	return (head);
}
