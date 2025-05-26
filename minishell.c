/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:06:27 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/26 16:06:29 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	e_status(130, 1);
	(void)sig;
}

void	check_ac(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell : no arguments please\n", 2);
		exit(127);
	}
}

void	init_main_ctx(t_main_ctx *ctx, char **env)
{
	ctx->input = NULL;
	ctx->expn = NULL;
	ctx->lst = NULL;
	ctx->exec = NULL;
	ctx->envp = init_env(env);
}

void	define_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
}

int	main(int argc, char **argv, char **env)
{
	t_main_ctx	ctx;

	check_ac(argc);
	(1) && (init_main_ctx(&ctx, env), argv = NULL);
	while (20052002)
	{
		define_sig();
		ctx.input = readline("minishell➤ ");
		if (!ctx.input)
			return (ft_putstr_fd("Exit\n", 1), 0);
		if (*ctx.input)
			add_history(ctx.input);
		if (ft_parse_command(ctx.input))
			continue ;
		(1) && (ctx.expn = exp_val(ctx.input, ctx.envp, 0), \
		ctx.lst = s_cmd(ft_split(ctx.expn), ctx.envp));
		if (!ctx.lst)
			continue ;
		(ft_expand(ctx.lst, ctx.envp), free(ctx.input));
		// for (t_token *tmp = ctx.lst; tmp ; tmp = tmp->next)
		// 	printf("{%s}\n", tmp->value);
		ctx.exec = convert_token_to_exec(ctx.lst, ctx.envp);
		if (!ctx.exec)
			continue ;
		execution(ctx.exec, &ctx.envp);
	}
	return (0);
}
