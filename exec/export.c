/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufarah <oufarah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:20:47 by oufarah           #+#    #+#             */
/*   Updated: 2025/05/05 02:30:40 by oufarah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_export(char *opt)
{
	int	i;

	i = 0;
	if (!((opt[i] >= 'A' && opt[i] <= 'Z') || (opt[i] >= 'a' && opt[i] <= 'z') \
		|| opt[i] == '_'))
		return (1);
	i++;
	while (opt[i])
	{
		if (!((opt[i] >= 'A' && opt[i] <= 'Z') || (opt[i] >= 'a' \
			&& opt[i] <= 'z') || (opt[i] >= '0' && opt[i] <= '9') \
			|| opt[i] == '_'))
		{
			if (opt[i] == '+' && opt[i +1] == '=')
				return (0);
			else if (opt[i] == '=')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	bubble_sort_env(t_env *env)
{
	int		swap;
	t_env	*ptr;

	if (!env)
		return ;
	swap = 1;
	while (swap)
	{
		swap = 0;
		ptr = env;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_env(ptr, ptr->next);
				swap = 1;
			}
			ptr = ptr->next;
		}
	}
}

int	ft_export(char **opt, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	if (!opt[1])
	{
		tmp = *env;
		bubble_sort_env(tmp);
		while (tmp)
		{
			if (tmp->key && !ft_strcmp("_", tmp->key))
			{
				tmp = tmp->next;
				continue ;
			}
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
			continue ;
		}
		tmp = find_env(*env, opt[i]);
		if (tmp)
		{
			if (tmp->value && !ft_strchr(opt[i], '='))
				continue ;
		}
		equal = ft_strstr(opt[i], "+=");
		if (equal)
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
