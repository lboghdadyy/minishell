/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logic_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:29:05 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/25 18:28:22 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_stop_redirect(t_token *lst, t_env *envp)
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
	(void)envp;
	if (f)
		return (0);
	return (1);
}

bool	check_assi(char *st, int index)
{
	int i1;

	i1 = index;
	while (st[index] && !ft_is_space(st[index]))
	{
		if (ft_strchr("+-=", st[index]))
			return (1);
		index++;
	}
	while (i1 >= 0 && !ft_is_space(st[i1]))
	{
		if (ft_strchr("+-=", st[i1]))
			return (1);
		i1--;
	}
	return (false);
}

bool	should_expand(char *s, t_expand e)
{
	return ((s[e.i] == '$' && !e.s_q && s[e.i + 1]
		&& !ft_strchr(" .:=", s[e.i + 1])
		&& !delimter(s, e.i)));
}

bool	is_invalid_dollar_after_op(t_expand_ctx *c)
{
	return ((c->s[c->e.i + 1] == '$' && check_assi(c->s, c->e.i) \
	&& c->st == 0) || ((c->s[c->e.i + 1] == '$' && c->s[c->e.i + 1]== '"' \
	&& c->e.d_q)));
}
