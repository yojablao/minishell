/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:25:23 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/04 12:43:20 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	bulting(t_exec_cmd **s, t_shell *data)
{
	
	if(!(*s)->args[0])
		return (0);
	if (ft_strcmp((*s)->args[0], "echo") == 0)
		return (echo((*s)->args), 1);
	if (ft_strcmp((*s)->args[0], "exit") == 0)
		return (exit_builting((*s)->args, 0), 1);
	else if (ft_strcmp((*s)->args[0], "unset") == 0)
		return (un_set_builting(s, &data->env), 1);
	else if (ft_strcmp((*s)->args[0], "cd") == 0)
		return (cd_builting(s, &data->env), 1);
	else if (ft_strcmp((*s)->args[0], "export") == 0)
		return (export_builtin((*s)->args, &data->env), 1);
	else if (ft_strcmp((*s)->args[0], "env") == 0)
		return (env_build(data->env->lenv,(*s)), 1);
	else if (ft_strcmp((*s)->args[0], "pwd") == 0)
		return (pwd_builting(data->env->lenv), 1);
	else
		return (0);
}

void	handle_error2(char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
	{
		perror(cmd);
		if (errno == ENOENT)
			get_exit(127, 0);
		else
			get_exit(errno, 0);
		exit(get_exit(0, 1));
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		errno = EISDIR;
		perror(cmd);
		get_exit(126, 0);
		exit(126);
	}
}

void	handel_errer(char *cmd)
{
	handle_error2(cmd);
	if (errno == EACCES)
	{
		perror(cmd);
		get_exit(126, 0);
		exit(126);
	}
	perror(cmd);
	get_exit(errno, 0);
	exit(1);
}

bool	child(t_exec_cmd **cmd, t_shell *data)
{
	if ((*cmd)->args && (*cmd)->args[0] && (*cmd)->args[0][0] == '\2')
		return (1);
	if ((*cmd)->args && (!(*cmd)->args[0] || !(*cmd)->args[0][0]))
		exit(0);
	filehandler(cmd);
	if (bulting(cmd, data))
	{
		add_to_env(&data->env->lenv, "_", (*cmd)->args[0], 0);
		get_exit(0, 0);
		exit(0);
	}
	else if ((*cmd)->cmd == NULL && (*cmd)->args[0])
	{
		comnond_err((*cmd)->args[0], data->env->lenv);
		return (get_exit(127, 0), exit(127), false);
	}
	else if ((*cmd)->cmd == NULL && (*cmd)->args == NULL)
		exit(1);
	if (execve((*cmd)->cmd, (*cmd)->args, data->env->env) == -1)
		handel_errer((*cmd)->cmd);
	return (EXIT_SUCCESS);
}

char	*f_strdup(const char *s1)
{
	char	*new;
	int		i;

	if (s1 == NULL)
		return (NULL);
	new = (char *)master(sizeof(char) * ft_strlen(s1) + 1, 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
