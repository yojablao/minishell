/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:07:54 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/04 03:40:32 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;
	enum status;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head -> content = content;
	if (ft_strcmp(head -> content, "|") == 0)
		head -> stat = PIPE;
	else if (ft_strcmp(head -> content, "<") == 0)
		head -> stat = INP;
	else if (ft_strcmp(head -> content, ">") == 0)
		head -> stat = OUT;
	else if (ft_strcmp(head -> content, "<<") == 0)
		head -> stat = HER;
	else if (ft_strcmp(head -> content, ">>") == 0)
		head -> stat = APP;
	else
		head -> stat = TEXT;
	head -> next = NULL;
	return (head);
}
