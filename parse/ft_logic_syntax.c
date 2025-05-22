/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:29:05 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/22 13:47:18 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_stop_redirect(t_token *lst)
{
	t_token	*tmp;
	bool	f;

	tmp = lst;
	f = false;
	while (tmp)
	{
		if (tmp->type == WORD)
			f = true;
		tmp = tmp->next;
	}
	if (f)
		return (0);
	return (1);
}
