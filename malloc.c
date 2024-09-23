/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 04:55:36 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/20 02:19:00 by hamrachi         ###   ########.fr       */
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

void	ft_free(t_list *a, char *s1, char *s2)
{
	ft_free_stack(a);
	free(s1);
	free(s2);
}
void	ft_free_array(char **s1)
{
	int i;

	i = 0;
	while (s1[i])
	{
		free(s1[i]);
		i++;
	}
	free(s1);
}
