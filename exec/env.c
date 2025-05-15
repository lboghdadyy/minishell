/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:15:31 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/15 16:08:58 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*equal;
	char	*key;
	char	*value;
	char	*pwd;

	env = NULL;
	pwd = getcwd(NULL, 0);
	if (!envp || !*envp)
	{
		key = ft_strdup("OLDPWD");
		value = NULL;
		ft_lstadd_back_exec(&env, ft_lstnew_exec(key, value));
		key = ft_strdup("PATH");
		value = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
		ft_lstadd_back_exec(&env, ft_lstnew_exec(key, value));
		key = ft_strdup("PWD");
		value = pwd;
		ft_lstadd_back_exec(&env, ft_lstnew_exec(key, ft_strdup(value)));
		key = ft_strdup("SHLVL");
		value = ft_strdup("1");
		ft_lstadd_back_exec(&env, ft_lstnew_exec(key, value));
	}
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
	free(pwd);
	return (env);
}

char	*get_env_value(t_env **env, char *path)
{
	t_env	*tmp;
	char	*value;

	tmp = find_env(*env, path);
	if (!tmp)
		return (NULL);
	value = ft_strdup(tmp->value);
	return (value);
}

t_env	*find_env(t_env	*env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
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
	char	*av[3];

	av[0] = ft_strdup("export");
	av[1] = ft_strjoin("_=", "/usr/bin/env");
	av[2] = NULL;
	ft_export(av, &env);
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
