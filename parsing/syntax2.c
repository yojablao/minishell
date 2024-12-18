/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:15:24 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/04 11:38:34 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_full_list(t_list **a, char *s, int c)
{
	char	**array;
	t_list	*tmp;
	int		i;

	array = NULL;
	tmp = NULL;
	array = f_split(s, c, '\t');
	if (!array)
		exit(1);
	i = 0;
	while (array[i])
	{
		tmp = f_lstnew(array[i]);
		if (!tmp)
			exit(1);
		ft_lstadd_back(a, tmp);
		i++;
	}
}

void	ft_free_stack(t_list *a)
{
	t_list	*tmp;
	t_list	*to_free;

	tmp = a;
	while (tmp)
	{
		to_free = tmp->next;
		free(tmp);
		tmp = to_free;
	}
	a = NULL;
}

int	ft_check_grammer(t_list *a)
{
	t_list	*tmp;

	if (!a)
		return (1);
	tmp = a;
	if (tmp->stat == PIPE || !tmp)
		return (0);
	while (tmp)
	{
		if (tmp && tmp->stat != TEXT && !tmp->next)
			return (0);
		if (tmp->stat != TEXT && tmp->stat != PIPE)
		{
			if (tmp->next && tmp->next->stat != TEXT)
				return (0);
		}
		if (tmp->stat == PIPE)
		{
			if (tmp->next && tmp->next->stat == PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
