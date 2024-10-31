/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandingtools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:21:01 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/01 00:44:29 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkexpand(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_exit_status(int status)
{
	char	*str;

	str = ft_itoa(status);
	return (str);
}

char	*expanding_values(char *key, t_env *env)
{
	t_env	*tmp;
	char	*value;

	tmp = env;
	if (key[0] >= '0' && key[0] <= '9')
		return (f_strdup(key + 1));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key) && env->flage == 0)
		{
			value = f_strdup(tmp->value);
			return (value);
		}
		if (!ft_strcmp(tmp->key, key) && env->flage == 1)
		{
			value = f_strdup(f_remove_spaces(tmp->value));
			return (value);
		}
		tmp = tmp->next;
	}
	return (f_strdup(""));
}
