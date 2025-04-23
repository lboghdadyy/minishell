#include "../minishell.h"

// case cd 			with no opt => go to home 
// case cd ~		with no opt => go to home 

// case cd - 		=> print old pwd

// case cd .. 		=> Relative Path
// ==== cd . 		=> Relative Path
// ==== cd folder 	=> Relative Path

// case cd /home/oufarah 	=> Absolute Path
// ==== cd /tmp			 	=> Absolute Path
// ==== cd /usr/local/bin	=> Absolute Path

// case cd .. with removed folder back
// cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// folder/A/B/C/D/..
// => cd ..
// folder/A/B/C/D/../..
// => cd ..
// folder/A/B/C/D/../../..
// => cd ..
// folder



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

int	change_dir(char *path, t_env **env)
{
	char	*oldpwd;
	char	*newpwd;

	if (chdir(path) == -1)
		return (perror("cd"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(get_env_value(env, "PWD"));
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		// perror("cd");
		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories\n", 2);
		newpwd = ft_strdup(path);
	}
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	ft_cd(char **opt, t_env **env)
{
	char	*home;
	char	*old_pwd;

	home = get_env_value(env, "HOME");
	if (!home)
		return(ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (!opt[1] || !(opt[1] && ft_strcmp(opt[1], "~"))) // HOME
		return (change_dir(home, env));
	old_pwd = get_env_value(env, "OLDPWD");
	if (!old_pwd)
		return(ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	if (opt[1] && !ft_strcmp(opt[1], "-")) // cd - old pwd
	{
		ft_putstr_fd(old_pwd, 1);
		ft_putstr_fd("\n", 1);
		return (change_dir(old_pwd, env));
	}
	else if (opt[1])
		return (change_dir(opt[1], env));
	return (0);
}
