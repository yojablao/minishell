/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:06:47 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/01 00:48:59 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	comond_init(t_shell **cmd)
{
	char	**comond;

	comond = ft_joinlist(&(*cmd)->a, &(*cmd)->env, -1);
	if (!handel_comond(comond, &(*cmd)->cmd, &(*cmd)->env))
		return (false);
	if (!(*cmd)->cmd->args[0])
		return (close_open_fd(&(*cmd)->cmd), false);
	if (check_internal_builtins(&(*cmd)->cmd, &(*cmd)->env) == 1)
		return (false);
	(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0], &(*cmd)->env->lenv);
	if (!(*cmd)->cmd->cmd)
		return (false);
	else
		add_to_env(&(*cmd)->env->lenv, "_", (*cmd)->cmd->cmd, 0);
	return (true);
}

static void	process_input(char *input, t_shell **data)
{
	int	flage;

	if (input && *input)
	{
		add_history(input);
		flage = parsing_input(data, input);
		if (flage == -1)
			close_open_fd(&(*data)->cmd);
		if (flage != -1 && g_sig == 0)
			exice(&(*data)->cmd, flage, data);
	}
}

void	handling_sig(int ac)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 1;
	(void)ac;
}

static void	minishell_loop(t_shell **data, char *prompt)
{
	char	*input;
	int		org_in;

	rl_catch_signals = 0 ;
	signal(SIGINT, handling_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(prompt);
		if (g_sig)
			get_exit(1, 0);
		org_in = dup(STDIN_FILENO);
		if (!input)
		{
			printf("exit\n");
			close(org_in);
			exit(0);
		}
		g_sig = 0;
		process_input(input, data);
		free(input);
		dup2(org_in, STDIN_FILENO);
		close(org_in);
		save_env(&(*data)->env);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*data;
	char	*prompt;

	(void)ac;
	(void)av;
	prompt = ft_strdup("\001\033[1;32m\002minishell\001\033[0m\002 : ");
	data = init(env);
	if (!data)
		return (1);
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		write(2, "not a tty!\n", 12);
		return (0);
	}
	minishell_loop(&data, prompt);
	return (0);
}
