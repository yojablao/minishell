/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:53:27 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/30 08:59:47 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_to_path(char *path, bool flag, int *err)
{
	char	buffer[1025];
	char	*tmp;

	tmp = getcwd(buffer, sizeof(buffer));
	if (!tmp)
		perror("minishell: cd: error retrieving current directory");
	if (chdir(path) == -1)
	{
		*err = 1;
		if (flag)
			perror("minishell: cd: HOME not set");
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		get_exit(1, 0);
		return (NULL);
	}
	if (!tmp)
		return (NULL);
	return (f_strdup(buffer));
}

void	update_pwd(char *pwd, char *oldpwd, bool flag, t_env **env)
{
	if (pwd)
		add_to_env(env, "PWD", pwd, flag);
	if (oldpwd)
		add_to_env(env, "OLDPWD", oldpwd, flag);
}

void	handle_fail_chdir(t_env **env, char *path)
{
	if (ft_strcmp(path, "..") == 0)
	{
		add_to_env(env, "OLDPWD", extract_value((*env), "PWD"), 0);
		add_to_env(env, "PWD", "/..", 1);
	}
	else if (ft_strcmp(path, ".") == 0)
	{
		add_to_env(env, "OLDPWD", extract_value((*env), "PWD"), 0);
		add_to_env(env, "PWD", "/.", 1);
	}
}

void	cd_builting(t_exec_cmd **s, t_environment **env)
{
	char	buffer[1025];
	char	*old;
	int		err;

	err = 0;
	if (!(*s)->args[1])
		old = cd_to_path(extract_value((*env)->lenv, "HOME"), 1, &err);
	else if (ft_strcmp((*s)->args[1], "-") == 0)
		old = cd_to_path(extract_value((*env)->lenv, "OLDPWD"), 1, &err);
	else
		old = cd_to_path((*s)->args[1], 0, &err);
	if (old)
	{
		update_pwd(getcwd(buffer, sizeof(buffer)), old, 0, &(*env)->lenv);
		(*env)->env = join_to_env((*env)->lenv);
	}
	else if (!old)
	{
		handle_fail_chdir(&(*env)->lenv, (*s)->args[1]);
		update_pwd(getcwd(buffer, sizeof(buffer)), old, 0, &(*env)->lenv);
	}
	if (!err)
		get_exit(0, 0);
}
