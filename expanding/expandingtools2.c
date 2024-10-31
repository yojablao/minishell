/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandingtools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:21:01 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/31 15:19:36 by yojablao         ###   ########.fr       */
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

char	*process_double_quote(char *tmp, t_env *env, char *buffer)
{
	int	j;

	j = 0;
	while (tmp[j])
	{
		buffer = handle_d_q_content(tmp, &j, env, buffer);
		j++;
	}
	return (buffer);
}
