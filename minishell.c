#include "minishell.h"

void	handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// set exit status to 130;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token *lst;
	t_exec	*exec;
	t_env	*envp;

	if (argc != 1)
		ft_exit("no arguments\n");
	envp = init_env(env);
	(void)argv;
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	while (1337)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		lst = ft_parse_command(input);
		if (!lst)
			continue ;
		ft_expand(lst);
		exec = convert_token_to_exec(lst);
		free(input);
		ft_lstclear(&lst);
		execution(exec, &envp, env); // I need more to work
	}
}
