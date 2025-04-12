#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;

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
		ft_parse_command(input);
		free(input);
	}
	// if is exec
	//     do execve;
	// else if built-ins
	//     execve;
}
