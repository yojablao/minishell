/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:25:15 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 12:25:54 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_my_malloc(size_t len)
{
	char	*new;

	new = master(len, 1);
	if (!new)
	{
		free(new);
		exit(1);
	}
	ft_memset(new, 0, len);
	return (new);
}

void	ft_free(t_list *a, char *s1, char *s2)
{
	ft_free_stack(a);
	free(s1);
	free(s2);
}

void	ft_free_array(char **s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		free(s1[i]);
		i++;
	}
	free(s1);
}

void	free_all(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
}
