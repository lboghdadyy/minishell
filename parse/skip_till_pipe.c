/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_till_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:30:49 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/21 11:30:51 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_till_pipe(t_token **lst)
{
	if (!lst)
		return ;
	while ((*lst)->next && (*lst)->next->type != PIPE)
		(*lst) = (*lst)->next;
}
