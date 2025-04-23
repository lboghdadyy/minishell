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

char	*ft_last_word(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i -= 1;
	while (s[i] != '/' && i >= 0)
		i--;
	if (i == 0)
		return (NULL);
	i += 1;
	return (s + i);
}

char	*ft_getprompt(void)
{
	char	*path;
	char	*prompt;
	char	*last_word;

	path = getcwd(NULL, 0);
	if (!path)
		return (RED"~ shell >");
	last_word = ft_last_word(path);
	prompt = ft_strjoin(RED"~ ", last_word);
	prompt = ft_strjoin(prompt, " 𒌐 "WHITE);
	free(path);
	return (prompt);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token *lst;
	t_exec	*exec;
	t_env	*envp;
	char	*prompt;

	if (argc != 1)
		ft_exit("no arguments\n");
	envp = init_env(env);
	(void)argv;
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	while (1337)
	{
		prompt = ft_getprompt();
		input = readline(prompt);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		lst = ft_parse_command(input);
		if (!lst)
			continue ;
		ft_expand(lst, envp);
		exec = convert_token_to_exec(lst);
		free(input);
		ft_lstclear(&lst);
		execution(exec, &envp); // I need more to work
	}
}
