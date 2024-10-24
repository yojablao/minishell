/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:06:47 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/24 22:13:52 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (flage != -1)
			exice(&(*data)->cmd, flage, data);
	}
}

static void	minishell_loop(t_shell **data, char *prompt)
{
	// int		stdin_backup;
	char	*input;

	while (1)
	{
		// signal(SIGINT, handl_int);
		signal(SIGQUIT, SIG_IGN);
		input = readline(prompt);
		if (!input)
		{
			printf("exit");
			exit(0);
		}
		process_input(input, data);
		free(input);
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