/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:19:24 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:16:41 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shell_lvl(t_env **env)
{
	char	*value;
	int		lvl;

	value = extract_value((*env), "SHLVL");
	lvl = ft_atoi(value);
	if (!value || !*value || lvl > 999)
		return (add_to_env(env, "SHLVL", "1", 0));
	if (lvl == 2147483647)
		return (add_to_env(env, "SHLVL", "0", 0));
	if (lvl < 0)
		return (add_to_env(env, "SHLVL", "0", 0));
	if (lvl == 999)
		return (add_to_env(env, "SHLVL", "", 0));
	value = ft_itoa(lvl + 1);
	add_to_env(env, "SHLVL", value, 0);
	free(value);
}

void	add_env(t_env **head, char *key, char *value)
{
	t_env	*new_env;
	t_env	*tmp;

	new_env = (t_env *)master(sizeof(t_env), 1);
	new_env->key = f_strdup(key);
	new_env->value = f_strdup(value);
	new_env->valid = 1;
	new_env->next = NULL;
	if (*head == NULL)
		*head = new_env;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}

t_env	*env_set(char **envi)
{
	t_env	*env;
	int		i;
	int		j;

	env = NULL;
	i = 0;
	if (!envi)
		return (NULL);
	while (envi[i])
	{
		j = 0;
		while (envi[i][j])
		{
			if (envi[i][j] == '=')
			{
				envi[i][j] = '\0';
				add_env(&env, &envi[i][0], &envi[i][j + 1]);
				envi[i][j] = '=';
				break ;
			}
			j++;
		}
		i++;
	}
	return (env);
}

int	typecheck(char *word, t_exec_cmd **comond)
{
	if (ft_strcmp(word, "<<") == 0)
	{
		if ((*comond)->infd != 0)
			close((*comond)->infd);
		return (1);
	}
	else if (ft_strcmp(word, "<") == 0)
	{
		if ((*comond)->infd != 0)
			close((*comond)->infd);
		return (2);
	}
	else if (ft_strcmp(word, ">>") == 0)
	{
		if ((*comond)->outfd != 1)
			close((*comond)->outfd);
		return (3);
	}
	else if (ft_strcmp(word, ">") == 0)
	{
		if ((*comond)->outfd != 1)
			close((*comond)->outfd);
		return (4);
	}
	return (0);
}
