/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:30:18 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/22 16:07:29 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_operator(char *string, int index, char c)
{
	int	count;

	count = 0;
	while (string[index] == c)
	{
		count++;
		index++;
	}
	return (count);
}

int ft_check_syntax(char *string)
{
	int		index;
	int		count;
	char	c;

	index = 0;
	count = 0;
	while (string[index])
	{
		if (string[index] == '<' || string[index] == '>')
		{
			c = string[index];
			if (ft_count_operator(string, index, string[index]) > 2)
				return (store_exit_status(2, 1), ft_syntax_error(), 1);
			while (string[index] == c)
				index++;
			while (string[index] == 32 || string[index] == '\t')
				index++;
			if (!string[index] || ft_strchr("|<>", string[index]))
				return (store_exit_status(2, 1), ft_syntax_error(), 1);
		}
		else if (string[index] == '|')
		{
			if (ft_count_operator(string, index, string[index]) > 1)
				return (store_exit_status(2, 1), ft_syntax_error(), 1);
			index++;
			while (string[index] == 32 || string[index] == '\t')
				index++;
			if (!string[index] || ft_strchr("|<>", string[index]))
				return (store_exit_status(2, 1), ft_syntax_error(), 1);
		}
		index++;
	}
	return 0;
}

int	ft_parse_command(char *string)
{
	if (string)
	{
		if (ft_check_quots(string))
			return (1);
		if (ft_check_syntax(string))
			return (1);
		if (ft_check_braces(string))
			return (1);
	}
	return (0);
}
