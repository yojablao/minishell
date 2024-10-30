/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandingtools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:21:01 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/26 18:39:01 by hamrachi         ###   ########.fr       */
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
