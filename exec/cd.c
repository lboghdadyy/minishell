#include "../minishell.h"

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

	home = get_env_value(env, "HOME");
	if (!home)
		return(ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (!opt[1])
		return (change_dir(home, env));
	else if (opt[1])
		return (change_dir(opt[1], env));
	return (0);
}
