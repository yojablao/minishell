/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 04:55:36 by hamrachi          #+#    #+#             */
/*   Updated: 2024/08/21 02:49:09 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_my_malloc(size_t len)
{
    char	*new;
	int i;

	new = malloc(len);
	if(!new)
	{
		free(new);
		exit(1);
	}
	i = 0;
	while (new[i])
	{
		new[i] = '\0';
		i++;
	}
	return(new);
}