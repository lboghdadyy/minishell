/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:28:53 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/28 13:22:37 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quotes_type(char *string)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (string[index] == '\'')
			return (SINGLE);
		if (string[index] == '\"')
			return (COUPLE);
		index++;
	}
	return (0);
}
