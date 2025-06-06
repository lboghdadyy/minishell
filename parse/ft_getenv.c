/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:26:02 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/06/05 17:56:17 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*g_env(char *value, int *index, t_env *envp)
{
	char	*sub;
	char	*found;
	size_t	skipped;
	t_env	*tmp;

	skipped = skip_variable(value, *index);
	sub = subs(value, *index + 1, skipped - 1);
	if (ft_strchr(sub, '{') || ft_strchr(sub, '}'))
		sub = ft_remove_bracets(sub);
	*index += skipped;
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
