/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:56:21 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/24 20:39:30 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delimter(char *s, int index)
{
	if (index == 0)
		return (0);
	index--;
	while ((s[index] == 32 || s[index] == '\t') && index >= 0)
		index--;
	if (index < 1)
		return (0);
	if (s[index] == '<' && s[index - 1] == '<')
		return (1);
	return (0);
}

void	join_before_va(char *nv, char *string, int i, int b_x)
{
	char	*sub;

	sub = ft_substr(string, b_x, i - b_x);
	nv = ft_strj(nv, sub);
}

char	*ft_expand_value(char *s, t_env *envp, int status)
{
	char				*nv;
	struct	s_expand	e;
	bool				reset;
	int					b_x;
	char				*sub;

	(1) && (nv = NULL, e.i = 0, reset = true, e.s_q = false, e.d_q = false);
	if (!ft_strchr(s, '$'))
		return (s);
	while (s[e.i])
	{
		if (reset)
			(1) && (b_x = e.i, reset = false);
		if (!s[e.i + 1])
		{
			e.i++;
			sub = ft_substr(s, b_x, e.i - b_x);
			nv = ft_strj(nv, sub);
		}
		else if (s[e.i] == '=' && status == 0 && s[e.i + 1] && s[e.i + 1] == '$')
			e.i += 2;
		else if (s[e.i] == '$' && !e.s_q && s[e.i + 1] && !ft_strchr(" \".:=", s[e.i + 1]) && !delimter(s, e.i))
		{
			sub = ft_substr(s, b_x, e.i - b_x);
			nv = ft_strj(nv, sub);
			if (s[e.i] == '$' && s[e.i + 1] == '?')
			{
				nv = ft_strj(nv, ft_itoa(store_exit_status(0, 0)));
				e.i += 2;
			}
			else
			{
				sub = ft_get_env(s, &e.i, envp);
				nv = ft_strj(nv, sub);
			}
			reset = true;
		}
		else if (s[e.i] == '\'' && !e.d_q)
		{
			e.s_q = !e.s_q;
			e.i++;
		}
		else if (s[e.i] == '\"' && !e.s_q)
		{
			e.d_q = !e.d_q;
			e.i++;
		}
		else
			e.i++;
	}
	return (nv);
}
