/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/15 17:47:39 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_syntax_error(void)
{
	ft_putstr_fd("minishell : Syntax error\n", 2);
}

int	delimter(char *s, size_t index)
{
	if (index >= ft_strlen(s))
		return (0);
	while (1)
	{
		if (index > 0 && s[index] == '<' && s[index - 1] == '<')
			return (1);
		if (index == 0)
			break ;
		index--;
	}
	return (0);
}

int	check_env(char *v, t_env *e)
{
	int			f;
	t_expand	ex;
	char		*exp;

	(1) && (f = 0, ex.i = 0, ex.d_q = false, ex.s_q = false);
	while (v[ex.i])
	{
		while (v[ex.i])
		{
			if (v[ex.i] == '$' && v[ex.i + 1] \
				&& id_check(v + ex.i + 1) && !ex.s_q && !ex.d_q)
				break ;
			if (v[ex.i] == '\'' && !ex.d_q)
				ex.s_q = !ex.s_q;
			else if (v[ex.i] == '\"' && !ex.s_q)
				ex.d_q = !ex.d_q;
			ex.i++;
		}
		if (!v[ex.i])
			break ;
		(1) && (exp = g_env(v + ex.i, e), ex.i += skip_variable(v, ex.i));
		if (check_for_s(exp))
			f = 1;
	}
	return (f);
}
