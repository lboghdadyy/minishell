#include "minishell.h"

void	handler(int sig)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	// rl_redisplay();
	store_exit_status(130, 1);
	(void)sig;
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
		return (ft_putstr_fd("minishell : no arguments\n", 2), 1);
	envp = init_env(env);
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	while (20052002)
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
		if (ft_parse_command(input))
			continue;
		expanded = ft_expand_value(input, envp, 0);
		free(input);
		lst = ft_split_command(ft_split(expanded));
		if (!lst)
			continue ;
		ft_expand(lst, envp);
		if (ft_stop_redirect(lst))
		{
			exec = convert_token_to_exec(lst, envp);
			continue ;
		}
		exec = convert_token_to_exec(lst, envp);
		if (!exec)
			continue ;
		execution(exec, &envp); // I need more to work
	}
}
