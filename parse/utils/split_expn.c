/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:31:15 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/13 21:00:35 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	skip_tillvar(char *val, size_t i)
{
	size_t	start;

	start = i;
	while (val[i] && val[i] != '$')
		i++;
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
	int			i;
	size_t		sub_ln;
	t_spli_cmd	s;
	int			b_i;
	char		*v_e;

	(1) && (i = 0, s.type = WORD);
	while (val[i])
	{
		(1) && (b_i = i, sub_ln = skip_tillvar(val, i));
		i += sub_ln;
		s.cmd = ft_remove_quotes(subs(val, b_i, sub_ln));
		if (!val[i])
		{
			s.cmd = ft_remove_quotes(s.cmd);
			return (ft_lstnew(lst, s, env, 1));
		}
		v_e = g_env(val, &i, env);
		add_to_lst(env, lst, acttual_split(v_e), s.cmd);
	}
}
