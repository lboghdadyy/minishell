/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bracets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:56:46 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/15 20:29:18 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_len_wo_q(char *value)
{
	size_t	count;
	size_t	i;
	size_t	count_inside;
	char	c;

	(1) && (i = 0, count = 0);
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
		{
			(1) && (c = value[i], count_inside = 0, i++);
			while (value[i] && value[i] != c)
				(1) && (count_inside++, i++);
			if (value[i] == c)
				i++;
			count += count_inside;
		}
		else
			(1) && (count++, i++);
	}
	return (count);
}

char	*remove_q(char *tmp)
{
	int		index;
	char	*clean;
	int		index_tmp;
	bool	s_q;
	bool	d_q;

	index = 0;
	(1) && (index_tmp = 0, s_q = false, d_q = false);
	if (!tmp)
		return (ft_strdup(""));
	clean = ft_malloc(ft_len_wo_q(tmp) + 1, ALLOC);
	while (tmp[index_tmp])
	{
		if (tmp[index_tmp] == '\'' && !d_q)
			(1) && (s_q = !s_q, index_tmp++);
		else if (tmp[index_tmp] == '\"' && !s_q)
			(1) && (d_q = !d_q, index_tmp++);
		else if (tmp[index_tmp] == '$' && !d_q && \
			!s_q && tmp[index_tmp + 1] && ft_strchr("\'\"", tmp[index_tmp + 1]))
			index_tmp++;
		else
			(1) && (clean[index] = tmp[index_tmp], index_tmp++, index++);
	}
	clean[index] = '\0';
	return (clean);
}

int	check_end(char *string, char c, int *index)
{
	while (string[*index] && string[*index] != c)
		(*index)++;
	if (!string[*index])
	{
		e_status(2, 1);
		ft_syntax_error();
		return (1);
	}
	return (0);
}

int	ft_check_braces(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == '{')
		{
			if (check_end(string, '}', &index))
				return (1);
			index++;
		}
		else if (string[index] == '}')
			return (e_status(2, 1), ft_syntax_error(), 1);
		else
			index++;
	}
	return (0);
}

int	check_case_rp(char *string, int *i)
{
	if (string[*i] == '>' && string[*i + 1] && string[*i + 1] == '|')
	{
		*i += 1;
		return (1);
	}
	return (0);
}
