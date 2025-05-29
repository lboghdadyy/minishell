/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bracets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:56:46 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/28 22:55:22 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

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
	if (ft_strchr(string, '{') || ft_strchr(string, '}'))
	{
		if (check_br(string))
			return (1);
	}
	return (0);
}

