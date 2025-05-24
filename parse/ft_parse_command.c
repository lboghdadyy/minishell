/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:30:18 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/24 20:19:26 by sbaghdad         ###   ########.fr       */
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

static	void	skip_s(char *s, int *i)
{
	while (s[*i] == 32 || s[*i] == '\t')
		*i += 1;
}

int	check_pip(char *s, int *i)
{
	if (s[*i] == '|')
	{
		if (ft_count_operator(s, *i, s[*i]) > 1)
			return (store_exit_status(2, 1), ft_syntax_error(), 1);
		*i += 1;
		skip_s(s, i);
		if (!s[*i] || s[*i] == '|')
			return (store_exit_status(2, 1), ft_syntax_error(), 1);
	}
	return (0);
}

int	ft_check_syntax(char *string)
{
	int		i;
	int		count;
	char	c;

	(1) && (i = 0, count = 0);
	while (string[i])
	{
		if (string[i] == '<' || string[i] == '>')
		{
			c = string[i];
			if (ft_count_operator(string, i, string[i]) > 2)
				return (store_exit_status(2, 1), ft_syntax_error(), 1);
			while (string[i] == c)
				i++;
			skip_s(string, &i);
			if (!string[i] || ft_strchr("|<>", string[i]))
				return (store_exit_status(2, 1), ft_syntax_error(), 1);
		}
		else if (check_pip(string, &i))
			return (1);
		i++;
	}
	return (0);
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
