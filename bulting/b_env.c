/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:26:36 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/04 16:24:31 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "env") == 0)
			i++;
		else
			return (args[i]);
	}
	return (NULL);
}

void	err(char *ptr)
{
	get_exit(127, 0);
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(ptr, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	env_build(t_env *env, t_exec_cmd *s)
{
	char	*ptr;

	ptr = check_args(s->args);
	if (!ptr)
	{
		while (env)
		{
			if (env->valid == 1)
			{
				ft_putstr_fd(env->key, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(env->value, 1);
				ft_putstr_fd("\n", 1);
			}
			env = env->next;
		}
		get_exit(0, 0);
	}
	else
		err(ptr);
	return (0);
}
