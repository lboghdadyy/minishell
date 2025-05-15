#include "minishell.h"

void	handler(int sig, siginfo_t *siginfo, void *no)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
		ft_malloc(0, CLEAR);
		exit(1);
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)siginfo;
	(void)no;
	// set exit status to 130;
}

#include <sys/types.h>
#include <dirent.h>


int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token *lst;
	t_exec	*exec;
	t_env	*envp;
	char	*expanded;
	struct sigaction	sa;
	
    DIR *dir = opendir("parse");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    closedir(dir);
	if (argc != 1)
		ft_exit("no arguments\n");
	envp = init_env(env);
	(void)argv;
	rl_catch_signals = 0;
	sa.sa_sigaction = &handler;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1337)
	{
		input = readline(RED"minishell➤ "WHITE);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		expanded = ft_expand_value(input, envp);
		// printf("%s\n", expanded);
		free(input);
		lst = ft_parse_command(expanded);
		if (!lst)
			continue ;
		ft_expand(lst, envp);
		exec = convert_token_to_exec(lst, envp);
		execution(exec, &envp); // I need more to work
	}
	ft_malloc(0, CLEAR);
}
