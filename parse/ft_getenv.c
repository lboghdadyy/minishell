/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:26:02 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/16 14:39:10 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*g_env(char *value, t_env *envp)
{
	char	*sub;
	char	*found;
	int		skipped;
	t_env	*tmp;

	skipped = skip_variable(value, 0);
	sub = subs(value, 1, skipped - 1);
	if (!ft_strcmp(sub, "?"))
		return (ft_itoa(e_status(0, 0)));
	tmp = find_env(envp, sub);
	if (!tmp)
		return (NULL);
	found = tmp->value;
	return (found);
}

void	default_sig(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	child_sig(char	*cmd)
{
	if (!ft_strcmp(cmd, "./minishell"))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
		signal(SIGQUIT, handler);
	recevied_from_inp(1, 1);
}

int	check_type_exp(t_tokentype type)
{
	if (type == EXPAN || type == SINGLEQ \
		|| type == DOUBLEQ || type == WORD)
		return (1);
	return (0);
}
