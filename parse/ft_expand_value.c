/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:56:21 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/22 13:58:52 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delimter(char *s, int index)
{
	if (index == 0)
		return (1);
	index--;
	while ((s[index] == 32 || s[index] == '\t') && index >= 0)
		index--;
	if (index < 1)
		return (0);
	if (s[index] == '<' && s[index - 1] == '<')
		return (1);
	return (0);
}

char	*ft_expand_value(char *s, t_env *envp, int status)
{
	char	*n_val;
	int		i;
	bool	reset;
	int		b_idx;
	bool	s_q;
	bool	d_q;
	char	*sub;

	(1) && (n_val = NULL, i = 0, reset = true, s_q = false, d_q = false);
	while (s[i])
	{
		if (reset)
			(1) && (b_idx = i, reset = false);
		if (!s[i + 1])
		{
			i++;
			sub = ft_substr(s, b_idx, i - b_idx);
			n_val = ft_strjoin(n_val, sub);
		}
		else if (s[i] == '=' && status == 0 && s[i + 1] && s[i + 1] == '$')
			i += 2;
		else if (s[i] == '$' && !s_q && s[i + 1] && !ft_strchr(" \".:=", s[i + 1]) && !delimter(s, i))
		{
			sub = ft_substr(s, b_idx, i - b_idx);
			n_val = ft_strjoin(n_val, sub);
			if (s[i] == '$' && s[i + 1] == '?')
				(1) && (n_val = ft_strjoin(n_val, ft_itoa(store_exit_status(0, 0))), i += 2);
			else if (s[i] == '$' && s[i + 1] == '$')
				(1) && (n_val = ft_strjoin(n_val, ft_itoa(getpid())), i += 2);
			else
			{
				sub = ft_get_env(s, &i, envp);
				n_val = ft_strjoin(n_val, sub);
			}
			reset = true;
		}
		else if (s[i] == '\'' && !d_q)
			(1) && (s_q = !s_q, i++);
		else if (s[i] == '\"' && !s_q)
			(1) && (d_q = !d_q, i++);
		else
			i++;
	}
	return (n_val);
}