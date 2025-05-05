/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:58:45 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/05 02:29:22 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_exit(char	*opt)
{
	if (!opt)
		return (1);
	if (*opt == '-' || *opt == '+')
		opt++;
	while (*opt)
	{
		if (*opt >= '0' && *opt <= '9')
			return (0);
		opt++;
	}
	return (1);
}

int	ft_exec_exit(char **opt)
{
	int	i;
	int	nbr;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (opt[0] && !opt[1])
		exit(13);// should exit with last exit status $?
	else if (is_valid_exit(opt[1]))
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(opt[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(2);
	}
	else if (opt[1] && !is_valid_exit(opt[1]) && !opt[2])
	{
		nbr = ft_atoi(opt[1]);
		exit(nbr);
	}
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return (1);
	}
	return (0);
}
