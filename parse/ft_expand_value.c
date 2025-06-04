/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_val.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:56:21 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/25 13:01:29 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_quotes(char *s, t_expand *e)
{
	if (s[e->i] == '\'' && !e->d_q)
	{
		e->s_q = !e->s_q;
		e->i++;
		return (true);
	}
	else if (s[e->i] == '\"' && !e->s_q)
	{
		e->d_q = !e->d_q;
		e->i++;
		return (true);
	}
	return (false);
}

void	init_expand_vars(char **nv, t_expand *e, bool *reset)
{
	*nv = NULL;
	e->i = 0;
	e->s_q = false;
	e->d_q = false;
	*reset = true;
}

char	*join_remove_quotes(char	*nv, char *sub)
{
	char	*unqoted;

	unqoted = ft_remove_quotes(sub);
	return (strj(nv, unqoted));
}

void	first_expand(t_expand_ctx *c)
{
	if (c->r)
		(1) && (c->b_x = c->e.i, c->r = false);
	if (!c->s[c->e.i + 1])
	{
		(1) && (c->e.i++, c->sub = subs(c->s, c->b_x, c->e.i - c->b_x));
		c->nv = join_remove_quotes(c->nv, c->sub);
	}
	else if (is_invalid_dollar_after_op(c))
		c->e.i++;
	else if (should_expand(c->s, c->e))
	{
		c->sub = subs(c->s, c->b_x, c->e.i - c->b_x);
		(1) && (c->nv = join_remove_quotes(c->nv, c->sub), c->r = true);
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

char	*exp_val(char *s, t_env *envp, int st)
{
	t_expand_ctx	ctx;

	ctx.nv = NULL;
	ctx.e.i = 0;
	ctx.e.s_q = false;
	ctx.e.d_q = false;
	ctx.r = true;
	ctx.envp = envp;
	ctx.st = st;
	ctx.s = s;
	if (st == 1)
	{
		printf("here\n");
		while (s[ctx.e.i])
			expand_loop_body(&ctx);
	}
	else
	{
		while (s[ctx.e.i])
			first_expand(&ctx);
	}
	return (ctx.nv);
}
