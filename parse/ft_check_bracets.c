/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bracets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:56:46 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/22 20:35:28 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_end(char *string, char c, int *index)
{
	while (string[*index] && string[*index] != c)
		*index += 1;
	if (!string[*index] || string[*index] != c)
		return (store_exit_status(2, 1), ft_syntax_error(), 1);
	if (string[*index] == c)
		*index += 1;
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
		}
		else if (string[index] == '}')
			return (store_exit_status(2, 1), ft_syntax_error(), 1);
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
