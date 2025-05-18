#include "minishell.h"

void	handler(int sig)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	store_exit_status(130, 1);
	(void)sig;
}

void ft_dupfds(int action)
{
	static int	fds[3];

	if (action == 0)
	{
		fds[0] = dup(0);
		fds[1] = dup(1);
		fds[2] = dup(2);
	}
	else
	{
		dup2(fds[0], 0);
		dup2(fds[1], 1);
		dup2(fds[2], 2);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token *lst;
	t_exec	*exec;
	t_env	*envp;
	char	*expanded;
	
    // DIR *dir = opendir("parse");
    // if (dir == NULL) {
    //     perror("opendir");
    //     return 1;
    // }
    // closedir(dir);
	if (argc != 1)
		ft_exit("no arguments\n");
	envp = init_env(env);
	(void)argv;
	rl_catch_signals = 0;
	ft_dupfds(0);
	signal(SIGQUIT, SIG_IGN);
	while (1337)
	{
		signal(SIGINT, &handler);
		input = readline("minishell➤ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		expanded = ft_expand_value(input, envp);
		free(input);
		lst = ft_parse_command(expanded);
		if (!lst)
			continue ;
		ft_expand(lst, envp);
		exec = convert_token_to_exec(lst, envp);
		execution(exec, &envp); // I need more to work
		ft_dupfds(1);
	}
}
