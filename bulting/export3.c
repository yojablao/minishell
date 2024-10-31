/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:24:47 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:29:50 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	find_target(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	add_key_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = master(sizeof(t_env), 1);
	if (!new_node)
		return ;
	new_node->key = f_strdup(key);
	new_node->value = f_strdup(value);
	new_node->valid = 0;
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
