/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:32:18 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/16 06:45:26 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_until_pipe(t_token *lst)
{
	int	count;

	count = 0;
	while (lst && lst->type != TOKEN_PIPE)
	{
		if (lst->type == TOKEN_WORD)
			count++;
		lst = lst->next;
	}
	return (count);
}

t_exec	*convert_token_to_exec(t_token *lst)
{
	t_exec	*head;
	t_exec	*node;
	t_exec	*current;
	int		ac;
	int		i;

	head = NULL;
	current = NULL;
	while (lst)
	{
		node = new_node(); // protect if fail
		ac = count_until_pipe(lst);
		node->opt = ft_malloc(sizeof(char *) * ac + 1, ALLOC);
		if (!node->opt)
			return (NULL);
		i = 0;
		while (lst && lst->type != TOKEN_PIPE)
		{
			if (lst->type == TOKEN_WORD)
			{
				node->opt[i] = ft_strdup(lst->value);
				if (i == 0)
					node->cmd = node->opt[0];
				i++;
			}
			lst = lst->next;
		}
		node->opt[i] = NULL;
		add_back(&head, node);
		if (lst && lst->type == TOKEN_PIPE)
			lst = lst->next;
	}
	return (head);
}

void	execution(t_exec *exec, char **env)
{
	if (ft_lstsize(exec) == 1 && is_builtin(exec->cmd))
		return (execute_builtin(exec, env)); // execute the builtin without forking and return
	while (exec)
	{
		// setup child
		if (is_builtin(exec->cmd))
			execute_builtin(exec, env);
		else
			execute_cmd(exec);
		exec = exec->next;
	}		
}
