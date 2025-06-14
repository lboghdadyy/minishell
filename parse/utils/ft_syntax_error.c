/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/14 20:49:01 by sbaghdad         ###   ########.fr       */
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

int	check_env(char *value, t_env *e)
{
	int		f;
	int		i;
	char	*exp;

	i = 0;
	f = 0;
	while (value[i])
	{
		i += skip_tillvar(value, i);
		if (!value[i])
			break ;
		exp = g_env(value, e);
		i += skip_variable(value, i);
		if (check_for_s(exp))
			f = 1;
	}
	return (f);
}
