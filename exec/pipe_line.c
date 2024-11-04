/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:46:03 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/04 12:46:18 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_pipe(t_shell *data, int curr_cmd)
{
	if (curr_cmd > 0)
	{
		if (dup2(data->prev[0], STDIN_FILENO) == -1)
			fail_case("minishell: dup2 failed\n");
	}
	if (curr_cmd < data->n_pipe)
	{
		if (dup2(data->curr[1], STDOUT_FILENO) == -1)
			fail_case("minishell: dup2 failed\n");
	}
	if (data->curr)
	{
		close(data->curr[0]);
		close(data->curr[1]);
	}
	if (data->prev)
	{
		close(data->prev[0]);
		close(data->prev[1]);
	}
}

pid_t	setup_pipe_and_fork(t_exec_cmd *cmd, t_shell *data, int curr_cmd)
{
	pid_t	pid;

	if (cmd->next != NULL)
	{
		if (pipe(data->curr) == -1)
			fail_case("pipe creation failed");
	}
	//signal(SIGINT, child_sig);
	// signal(SIGQUIT, child_sig);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		fail_case("fork failed");
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipe_handle(data, curr_cmd);
		dup_pipe(data, curr_cmd);
		child(&cmd, data);
	}
	return (pid);
}

void	close_ans_update(t_shell **data, int curr_cmd)
{
	if ((*data)->prev[0] != -1)
	{
		close((*data)->prev[0]);
		close((*data)->prev[1]);
	}
	if (curr_cmd != (*data)->n_pipe)
	{
		(*data)->prev[0] = (*data)->curr[0];
		(*data)->prev[1] = (*data)->curr[1];
	}
}

void	wait_for_process(pid_t pid)
{
	int	status;

	while (wait(&status) > 0)
		;
	get_exit(handel_wait_sig(pid, status, 1), 0);
}

void	pipe_line(t_exec_cmd **s, t_shell **data)
{
	int			curr[2];
	int			prev[2];
	int			curr_cmd;
	pid_t		pid;
	t_exec_cmd	*cmd;

	cmd = (*s);
	prev[0] = -1;
	prev[1] = -1;
	curr[0] = -1;
	curr[1] = -1;
	curr_cmd = 0;
	(*data)->curr = curr;
	(*data)->prev = prev;
	while (cmd != NULL)
	{
		pid = setup_pipe_and_fork(cmd, *data, curr_cmd);
		close_ans_update(data, curr_cmd++);
		cmd = cmd->next;
	}
	cmd = (*data)->head;
	wait_for_process(pid);
}
