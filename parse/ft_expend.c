/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:19:45 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/24 20:24:32 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_variable(char *value, int index)
{
	int	count;

	count = index + 1;
	if (value[count] == '$' || (value[count] >= '0' && value[count] <= '9'))
		return (2);
	if (value[count] == '{')
	{
		while (value[count] != '}')
			count++;
		count++;
		return (count - index);
	}
	while (value[count] && !ft_strchr("\"\' \t$.+[]={}", value[count]))
		count++;
	return (count - index);
}

size_t	ft_len_wo_quotes(char *value)
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

char	*ft_get_env(char *value, int *index, t_env *envp)
{
	char	*sub;
	char	*found;
	size_t	skipped;
	t_env	*tmp;

	skipped = skip_variable(value, *index);
	sub = ft_substr(value, *index + 1, skipped - 1);
	if (ft_strchr(sub, '{') || ft_strchr(sub, '}'))
		sub = ft_remove_bracets(sub);
	*index += skipped;
	tmp = find_env(envp, sub);
	if (!tmp)
		return (NULL);
	found = tmp->value;
	return (found);
}

void	ft_remove_quotes(t_token *tmp)
{
	int		index;
	char	*clean;
	int		index_tmp;
	bool	s_q;
	bool	d_q;

	(1) && (index = 0, index_tmp = 0, s_q = false, d_q = false);
	if (!tmp->value)
	{
		tmp->value = ft_strdup("");
		return ;
	}
	clean = ft_malloc(ft_len_wo_quotes(tmp->value) + 1, ALLOC);
	while (tmp->value[index_tmp])
	{
		if (tmp->value[index_tmp] == '\'' && !d_q)
			(1) && (s_q = !s_q, index_tmp++);
		else if (tmp->value[index_tmp] == '\"' && !s_q)
			(1) && (d_q = !d_q, index_tmp++);
		else
			(1) && (clean[index] = tmp->value[index_tmp], index_tmp++, index++);
	}
	clean[index] = '\0';
	tmp->value = clean;
}

void	ft_expand(t_token *lst, t_env *envp)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == SINGLEQ || tmp->type == DOUBLEQ || tmp->type == WORD)
		{
			if (ft_strchr(tmp->value, '$'))
				tmp->value = ft_expand_value(tmp->value, envp, 1);
			ft_remove_quotes(tmp);
			tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}
