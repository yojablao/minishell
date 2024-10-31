/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:25:41 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:28:52 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**join_to_env(t_env *env)
{
	int		i;
	char	**envi;

	if (!env)
		return (NULL);
	envi = master(sizeof(char *) * (size_env(env) + 2), 1);
	i = 0;
	while (env)
	{
		if (env->valid || ft_strcmp(env->key, "PATH") == 0)
		{
			envi[i] = f_strjoin(env->key, "=");
			envi[i] = f_strjoin(envi[i], env->value);
		}
		else
			envi[i] = f_strdup(env->key);
		i++;
		env = env->next;
	}
	envi[i] = NULL;
	return (envi);
}

bool	un_set_builting(t_exec_cmd **s, t_environment **env)
{
	int	i;
	int	err;

	err = 0;
	i = 1;
	if (!(*s))
		return (false);
	if (!(*env)->lenv)
		(*env)->lenv = env_set((*env)->env);
	while ((*s)->args[i])
	{
		if (is_valid_identifier((*s)->args[i], 1) == 0)
			un_set((*s)->args[i], env);
		else
		{
			print_error("not a valid identifier\n", (*s)->args[i], "unset");
			err = 1;
		}
		i++;
	}
	if (err)
		get_exit(1, 0);
	else
		get_exit(0, 0);
	return (true);
}

bool	check_exs(t_env **tmp, char *key, char *value, bool add)
{
	bool	flage;
	t_env	*env;

	env = (*tmp);
	flage = false;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			flage = true;
			env->valid = 1;
			if (add)
				env->value = f_strjoin(env->value, value);
			else
				env->value = f_strdup(value);
			break ;
		}
		env = env->next;
	}
	return (flage);
}

void	add_to_env(t_env **envi, char *key, char *content, bool add)
{
	t_env	*current;
	t_env	*new_node;
	bool	flage;

	current = *envi;
	flage = false;
	if (check_exs(envi, key, content, add) == true)
		return ;
	while (current->next)
		current = current->next;
	new_node = master(sizeof(t_env), 1);
	new_node->key = f_strdup(key);
	new_node->value = f_strdup(content);
	new_node->valid = 1;
	new_node->next = NULL;
	if (!current)
		*envi = new_node;
	else
		current->next = new_node;
}

void	delet_from_env(t_env **envi, char *s)
{
	t_env	*tmp;
	t_env	*current;

	tmp = NULL;
	current = *envi;
	while (current)
	{
		if (ft_strcmp(current->key, s) == 0)
		{
			if (tmp == NULL)
				*envi = current->next;
			else
				tmp->next = current->next;
			get_exit(0, 1);
			break ;
		}
		tmp = current;
		current = current->next;
	}
	get_exit(1, 1);
}

bool	un_set(char *s, t_environment **env)
{
	t_env	*envi;

	if (!env || !*env || !s)
		return (get_exit(1, 0), false);
	if (!(*env)->lenv)
		envi = env_set((*env)->env);
	else
		envi = (*env)->lenv;
	delet_from_env(&envi, s);
	(*env)->env = join_to_env((*env)->lenv);
	if (!(*env)->env)
		return (get_exit(1, 0), false);
	return (get_exit(0, 0), true);
}
