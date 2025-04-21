/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:15:31 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/21 16:16:07 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*equal;
	char	*key;
	char	*value;

	env = NULL;
	while (*envp)
	{
		equal = ft_strchr(*envp, '=');
		if (equal)
		{
			key = ft_substr(*envp, 0, equal - *envp);
			value = ft_strdup(equal + 1);
		}
		else
		{
			key = ft_strdup(*envp);
			value = NULL;
		}
		ft_lstadd_back_exec(&env, ft_lstnew_exec(key, value));
		envp++;
	}
	return (env);
}

char	**convert_t_env(t_env *env)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize_env(env);
	ret = ft_malloc(sizeof(char *) * (size + 1), ALLOC);
	while (env)
	{
		if (env->key && env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			ret[i] = ft_strjoin(tmp, env->value);
			i++;
		}
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	ft_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}
