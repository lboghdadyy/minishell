/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/28 10:21:59 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_syntax_error(void)
{
	ft_putstr_fd("minishell : Syntax error\n", 2);
}

int	delimter(char *s, size_t index)
{
	if (index >= ft_strlen(s))
		return (0);
	while (1)
	{
		if (index > 0 && s[index] == '<' && s[index - 1] == '<')
			return (1);
		if (index == 0)
			break ;
		index--;
	}
	return (0);
}
