/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:30:05 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/04 17:30:14 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_loop_body(t_expand_ctx *c)
{
	if (c->r)
		(1) && (c->b_x = c->e.i, c->r = false);
	if (!c->s[c->e.i + 1])
	{
		(1) && (c->e.i++, c->sub = subs(c->s, c->b_x, c->e.i - c->b_x));
		c->nv = strj(c->nv, c->sub);
	}
	else if (is_invalid_dollar_after_op(c))
		c->e.i++;
	else if (should_expand(c->s, c->e))
	{
		c->sub = subs(c->s, c->b_x, c->e.i - c->b_x);
		(1) && (c->nv = strj(c->nv, c->sub), c->r = true);
		if (c->s[c->e.i + 1] == '?')
			(1) && (c->nv = strj(c->nv, ft_itoa(e_status(0, 0))), c->e.i += 2);
		else
		{
			c->sub = g_env(c->s, &c->e.i, c->envp);
			c->nv = strj(c->nv, c->sub);
		}
	}
	else if (handle_quotes(c->s, &c->e))
		return ;
	else
		c->e.i++;
}
