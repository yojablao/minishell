/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:27:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:31:34 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
