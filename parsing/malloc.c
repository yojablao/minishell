/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 04:55:36 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/04 11:00:27 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*master(size_t size, int flag)
{
	static void	*arr[INT32_MAX];
	static int	i = 0;
	void		*ptr;

	if (flag == 1)
	{
		ptr = malloc(size);
		ft_bzero(ptr, size);
		if (!ptr)
			exit(1);
		arr[i] = ptr;
		arr[++i] = NULL;
		return (ptr);
	}
	else
	{
		i = 0;
		free_all(arr);
		return (NULL);
	}
}

void	*f_calloc(size_t count, size_t size)
{
	void	*str;

	if (size > sizeof(size))
		return (NULL);
	str = master(count * size, 1);
	if (!str)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}

t_list	*f_lstnew(void *content)
{
	t_list		*head;

	head = (t_list *)master(sizeof(t_list), 1);
	if (!head)
		return (NULL);
	head->content = content;
	if (ft_strcmp(head->content, "|") == 0)
		head->stat = PIPE;
	else if (ft_strcmp(head->content, "<") == 0)
		head->stat = INP;
	else if (ft_strcmp(head->content, ">") == 0)
		head->stat = OUT;
	else if (ft_strcmp(head->content, "<<") == 0)
		head->stat = HER;
	else if (ft_strcmp(head->content, ">>") == 0)
		head->stat = APP;
	else
		head->stat = TEXT;
	head->next = NULL;
	return (head);
}
