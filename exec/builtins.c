/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:27:12 by oufarah           #+#    #+#             */
/*   Updated: 2025/04/19 15:21:13 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env = NULL;
	char	*equal;
	char	*key;
	char	*value;

	while (*envp)
	{
		equal = strchr(*envp, '=');
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

int	ft_env(char **env)
{
	while (*env)
	{
		if (ft_strchr(*env, '='))
		{
			ft_putstr_fd(*env, 1);
			ft_putstr_fd("\n", 1);
		}
		env++;
	}
	return (0);
}

int	is_valid_option(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	int	nline;
	int	i;

	i = 1;
	nline = 0;
	while (cmd[i] && is_valid_option(cmd[i]))
	{
		nline = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!nline)
		write(1, "\n", 1);
	return (0);
}

int	ft_pwd(void)
{
	char	*a;

	a = getcwd(NULL, 0);
	if (a)
	{
		ft_putstr_fd(a, 1);
		ft_putstr_fd("\n", 1);
		free(a);
		return (0);
	}
	// perror("pwd :"); error handling
	return (1);
}

int is_valid_export(char *opt)
{
	int i = 0;

	if (!((opt[i] >= 'A' && opt[i] <= 'Z') || (opt[i] >= 'a' && opt[i] <= 'z') || opt[i] == '_'))
		return (1);
	i++;
	while (opt[i])
	{
		if (!((opt[i] >= 'A' && opt[i] <= 'Z') || (opt[i] >= 'a' && opt[i] <= 'z') || (opt[i] >= '0' && opt[i] <= '9') || opt[i] == '_'))
		{
			if (opt[i] == '+' && opt[i+1] == '=')
				return (0);
			else if (opt[i] == '=')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
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

int	ft_export(char **opt, t_env **env)
{
	int i = 0;
	char *key, *value, *equal;
	t_env	*tmp;

	if (!opt[1])
	{
		tmp = *env;
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
		return (0);
	}
	while (opt[++i])
	{
		if (is_valid_export(opt[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(opt[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue;
		}
		if ((equal = ft_strstr(opt[i], "+=")))
		{
			key = ft_substr(opt[i], 0, equal - opt[i]);
			value = ft_strdup(equal + 2);
			tmp = find_env(*env, key);
			if (tmp && tmp->value)
				tmp->value = ft_strjoin(tmp->value, value);
			else if (tmp)
				tmp->value = value;
			else
				ft_lstadd_back_exec(env, ft_lstnew_exec(key, value));
		}
		else
		{
			equal = ft_strchr(opt[i], '=');
			if (equal)
			{
				key = ft_substr(opt[i], 0, equal - opt[i]);
				value = ft_strdup(equal + 1);
			}
			else
			{
				key = ft_strdup(opt[i]);
				value = NULL;
			}
			tmp = find_env(*env, key);
			if (tmp)
				tmp->value = value;
			else
				ft_lstadd_back_exec(env, ft_lstnew_exec(key, value));
		}
	}
	return (0);
}
int ft_unset(char **opt, t_env **env)
{
	(void)opt;
	(void)env;
	return 0;
}
int ft_cd(char **opt, t_env **env)
{
	(void)opt;
	(void)env;
	return 0;
}
int	ft_exec_exit(char **opt)
{
	(void)opt;
	return 0;
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_exec *exec, t_env **env, char **envp)
{
	if (!ft_strcmp(exec->cmd, "echo"))
		ft_echo(exec->opt);
	else if (!ft_strcmp(exec->cmd, "cd"))
		ft_cd(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(exec->cmd, "export"))
		ft_export(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "unset"))
		ft_unset(exec->opt, env);
	else if (!ft_strcmp(exec->cmd, "env"))
		ft_env(envp);
	else if (!ft_strcmp(exec->cmd, "exit"))
		ft_exec_exit(exec->opt);
}
