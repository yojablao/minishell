/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/04 18:20:29 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_fd(int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("errer");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("errer");
	close(fd[1]);
	close(fd[0]);
}

int	check_internal_builtins(t_exec_cmd **s, t_environment **env)
{
	int	fds[2];
	int	suc;

	fds[1] = dup(STDOUT_FILENO);
	fds[0] = dup(STDIN_FILENO);
	suc = 0;
	if (internel_builting((*s)->args[0]))
	{
		filehandler(s);
		suc = exec_builtin(s, env);
		add_to_env(&(*env)->lenv, "_", (*s)->args[0], 0);
	}
	reset_fd(fds);
	return (suc);
}

bool	internel_builting(char *s)
{
	if (ft_strcmp(s, "env") == 0 || ft_strcmp(s, "pwd") == 0)
		return (1);
	else if (ft_strcmp(s, "exit") == 0 || ft_strcmp(s, "unset") == 0
		|| ft_strcmp(s, "cd") == 0 || ft_strcmp(s, "export") == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_exec_cmd **s, t_environment **env)
{
	if (ft_strcmp((*s)->args[0], "exit") == 0)
		return (exit_builting((*s)->args, 1), 1);
	if (ft_strcmp((*s)->args[0], "unset") == 0)
		return (un_set_builting(s, env), 1);
	if (ft_strcmp((*s)->args[0], "cd") == 0)
		return (cd_builting(s, env), 1);
	if (ft_strcmp((*s)->args[0], "export") == 0)
		return (export_builtin((*s)->args, env), 1);
	if (ft_strcmp((*s)->args[0], "env") == 0)
		return (env_build((*env)->lenv, (*s)), 1);
	if (ft_strcmp((*s)->args[0], "pwd") == 0)
		return (pwd_builting((*env)->lenv), 1);
	return (0);
}

int	exice(t_exec_cmd **cmd, int type, t_shell **info)
{
	if (type == 2)
		pipe_line(cmd, info);
	else
		execution_one(cmd, info);
	close_open_fd_1(&(*info)->head);
	return (1);
}
