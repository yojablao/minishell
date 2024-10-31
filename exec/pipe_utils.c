/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:54:55 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:25:29 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_open_fd(t_exec_cmd **data)
{
	t_exec_cmd	*cmd;

	cmd = (*data);
	if (cmd->infd != -1 && cmd->infd != 0)
		close(cmd->infd);
	if (cmd->infd != -1 && cmd->outfd != 1)
		close(cmd->outfd);
}

void	close_open_fd_1(t_exec_cmd **data)
{
	t_exec_cmd	*cmd;

	cmd = (*data);
	while (cmd)
	{
		if (cmd->infd != -1 && cmd->infd != 0)
			close(cmd->infd);
		if (cmd->outfd != 1 && cmd->infd != -1)
			close(cmd->outfd);
		cmd = cmd->next;
	}
}

int	get_exit(int sts, bool set)
{
	static int	status;

	if (!set)
		status = sts;
	return (status);
}
