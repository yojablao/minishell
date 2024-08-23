/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:01:50 by hamrachi          #+#    #+#             */
/*   Updated: 2023/12/12 20:50:51 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;
	t_list	*old;

	if (!lst || !del)
	{
		return ;
	}
	old = *lst;
	while (old != NULL)
	{
		new = old -> next;
		del(old -> content);
		free(old);
		old = new;
	}
	*lst = NULL;
}
