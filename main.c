/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:06:47 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/25 01:58:17 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 0;

// static void	restore_stdin(int stdin_backup)
// {
// 	if (stdin_backup != -1)
// 	{
// 		dup2(stdin_backup, STDIN_FILENO);
// 		close(stdin_backup);
// 	}
// }

// static int	backup_stdin(void)
// {
// 	int	stdin_backup;

// 	stdin_backup = dup(STDIN_FILENO);
// 	if (stdin_backup == -1)
// 		perror("dup");
// 	return (stdin_backup);
// }

static void	process_input(char *input, t_shell **data)
{
	int	flage;

	if (*input)
	{
		add_history(input);
		flage = pars(data, input);
		if (flage != -1 && g_sig == 0)
			exice(&(*data)->cmd, flage, data);
	}
}
void handling_sig(int ac)
{
    write(1,"\n",1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)ac;
}
static void	minishell_loop(t_shell **data, char *prompt)
{
	char	*input;
	int		org_in;

	signal(SIGINT, handling_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_sig = 0;
		input = readline(prompt);
		org_in = dup(STDIN_FILENO);
		if (!input)
		{
			printf("exit");
			close(org_in);
			exit(0);
		}
		process_input(input, data);
		free(input);
		dup2(org_in, STDIN_FILENO);
		close(org_in);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*data;
	char	prompt[] = "\x1B[36mminishell\x1B[0m : ";

	(void)ac;
	(void)av;
	data = init(env);
	if (!data)
		return (1);
	rl_catch_signals = 0;
	minishell_loop(&data, prompt);
	
	return (0);
}