/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:53:57 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/04 18:46:27 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	handle_infd(int *j, char **words, t_exec_cmd **cmd)
{
	if (!words[*j + 1])
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		get_exit(1, 0);
		return (false);
	}
	else
		(*cmd)->infd = in_redirect(words[++(*j)]);
	if ((*cmd)->infd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(words[(*j)]);
		get_exit(1, 0);
		if ((*cmd)->outfd != -1 && (*cmd)->outfd != 1)
			close((*cmd)->outfd);
		return (false);
	}
	return (true);
}

static bool	handle_outfd(int type, int *j, char **words, t_exec_cmd **cmd)
{
	if (!words[*j + 1])
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		get_exit(1, 0);
		return (false);
	}
	if (type == 3)
		(*cmd)->outfd = append(words[++(*j)]);
	else
		(*cmd)->outfd = out_redirect(words[++(*j)]);
	if ((*cmd)->outfd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(words[(*j)]);
		get_exit(1, 0);
		if ((*cmd)->infd != -1 && (*cmd)->infd != 0)
			close((*cmd)->infd);
		return (false);
	}
	return (true);
}

bool	handel_redirect(int *j, char **words, t_exec_cmd **cmd,
		t_environment **env)
{
	int	type;

	type = typecheck(words[*j], cmd);
	if (type == 1)
		(*cmd)->infd = ft_herdoc(words[++(*j)], env);
	if (type == 2)
		return (handle_infd(j, words, cmd));
	else if (type == 3 || type == 4)
		return (handle_outfd(type, j, words, cmd));
	return (true);
}

void	handel_pipe_cmd(t_shell **cmd)
{
	if (!internel_builting((*cmd)->cmd->args[0]))
	{
		(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],
				&(*cmd)->env->lenv);
		if ((*cmd)->cmd->cmd)
			add_to_env(&(*cmd)->env->lenv, "_", (*cmd)->cmd->cmd, 0);
		else
		{
			if ((*cmd)->cmd->args[0])
				(*cmd)->cmd->args[0][0] = '\0';
		}
	}
}

bool	init_pipe_line(t_shell **cmd)
{
	char	**comond;
	int		j;

	j = 0;
	while ((*cmd)->n_pipe >= j)
	{
		comond = ft_joinlist(&(*cmd)->a, &(*cmd)->env, -1);
		if((*cmd)->env->lenv)
			(*cmd)->env->lenv->flage += j;
		if (handel_comond(comond, &(*cmd)->cmd, &(*cmd)->env))
			handel_pipe_cmd(cmd);
		if ((*cmd)->n_pipe >= j + 1)
		{
			(*cmd)->cmd->next = aloc_comond((*cmd)->head);
			get_exit(0, 0);
		}
		else
			break ;
		if (!(*cmd)->cmd->next)
			return (get_exit(1, 0), false);
		(*cmd)->cmd = (*cmd)->cmd->next;
		j++;
	}
	return (get_exit(0, 1), true);
}
