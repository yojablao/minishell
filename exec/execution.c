/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:47:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/01 02:32:38 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_handle(t_shell *sh, int curr_cmd)
{
	if (curr_cmd == 0)
		sh->prev = NULL;
	if (curr_cmd == sh->n_pipe)
		sh->curr = NULL;
}

void	fail_case(char *fail)
{
	perror(fail);
	get_exit(1, 0);
	exit(EXIT_FAILURE);
}

void	child_sig(int sig)
{
	if (sig == SIGQUIT)
		printf("Quit: 3");
	printf("\n");
}

int	handel_wait_sig(pid_t pid, int status, bool p)
{
	int	signal;

	if (!p)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGPIPE)
			return (0);
		if (signal == SIGQUIT)
			printf("Quit: 3\n");
		else if (signal == SIGINT)
			printf("\n");
		return (128 + signal);
	}
	return (0);
}

int	execution_one(t_exec_cmd **s, t_shell **data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (child(s, (*data)) == EXIT_FAILURE)
			return (1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		get_exit(handel_wait_sig(pid, 0, 0), 0);
		signal(SIGINT, handling_sig);
	}
	return (0);
}
