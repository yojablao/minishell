/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:27:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:33:22 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	size_env(t_env *tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL)
	{
		if (!tmp->value && !tmp->key)
			break ;
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*extract_value(t_env *env, char *key)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
