/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_bracets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:22:13 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/24 18:23:07 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bad_substitution(void)
{
	ft_putstr_fd("minishell : bad substitution\n", 2);
}

int	check_br(char *string)
{
	int	index;

	if (!string)
		return (1);
	index = 0;
	while (string[index])
	{
		while (string[index] && string[index] != '$')
			index++;
		if (string[index] == '$' && string[index + 1] == '{')
		{
			index++;
			if (string[index + 1] == '}')
				return (bad_substitution(), 1);
			while (string[index] && string[index] != '}')
			{
				if (ft_strchr("$.@#$^&*()\t ", string[index]))
					return (bad_substitution(), 1);
				index++;
			}
		}
	}
	return (0);
}

int	len_without_br(char *string)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (string[index])
	{
		if (string[index] != '{' || string[index] != '}')
			count++;
		index++;
	}
	return (count);
}

char	*ft_remove_bracets(char *string)
{
	int		index;
	int		i;
	char	*clean;
	size_t	len;

	index = 0;
	i = 0;
	len = len_without_br(string);
	if (len == 0)
	{
		printf("case 3\n");
		return (bad_substitution(), NULL);
	}
	clean = ft_malloc(len + 1, ALLOC);
	while (string[index])
	{
		if (!ft_strchr("{}", string[index]))
		{
			clean[i] = string[index];
			i++;
		}
		index++;
	}
	clean[i] = 0;
	return (clean);
}
