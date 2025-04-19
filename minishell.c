#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token *lst;
	t_exec	*exec;
	t_env	*envp;

	if (argc != 1)
		ft_exit("no arguments\n");
	(void)argv;
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
		exec = convert_token_to_exec(lst);
		free(input);
		ft_lstclear(&lst);
		envp = init_env(env);
		execution(exec, &envp, env); // I need more to work
	}
}
