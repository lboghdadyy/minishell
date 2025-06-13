/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bracets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:56:46 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/13 15:55:02 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
