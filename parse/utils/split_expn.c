/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:31:15 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/14 21:55:05 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	skip_tillvar(char *val, size_t i)
{
	size_t	start;

	start = i;
	while (val[i])
	{
		if (val[i] == '$' && id_check(val + i + 1))
			break ;
		i++;
	}
	return (i - start);
}

void	add_to_lst(t_env *env, t_token **lst, char **list, char *cmd)
{
	t_spli_cmd	s;
	int			j;

	(1) && (j = 0, s.type = WORD);
	while (list[j])
	{
		if (j == 0)
		{
			s.cmd = strj(cmd, list[j++]);
			ft_lstnew(lst, s, env, 1);
		}
		else
		{
			s.cmd = list[j++];
			ft_lstnew(lst, s, env, 1);
		}
	}
}

void	ft_split_expanded(char *val, t_token **lst, t_env *env)
{
	size_t			sub_ln;
	t_expand_ctx	ctx;
	t_spli_cmd		s;
	char			*rmp;
	char			*v_e;

	s.type = WORD;
	init_expan(&ctx, val, env);
	while (val[ctx.i])
	{
		(1) && (ctx.b_x = ctx.i, sub_ln = skip_tillvar(val, ctx.i));
		ctx.i += sub_ln;
		rmp = subs(val, ctx.b_x, sub_ln);
		s.cmd = ft_remove_quotes(&ctx, rmp);
		if (!val[ctx.i])
			return (ft_lstnew(lst, s, env, 1));
		v_e = g_env(val + ctx.i, env);
		ctx.i += skip_variable(val, ctx.i);
		add_to_lst(env, lst, acttual_split(v_e), s.cmd);
	}
}
