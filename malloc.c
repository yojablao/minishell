/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 04:55:36 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/03 10:08:09 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_my_malloc(size_t len)
{
    char	*new;
	size_t i;

	new = c_malloc(len,1);
	if(!new)
	{
		free(new);
		exit(1);
	}
	i = 0;
	while (i < len)
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
t_malloc    *ft_mallocnew(void *value)
{
    t_malloc    *node;

    node = malloc(sizeof(t_malloc));
    if (!node)
        return (NULL);
    printf("\n\nadd of node : %p\n\n", node);
    node->ptr = value;
    node->next = NULL;
    return (node);
}

void    ft_mallocadd_back(t_malloc **lst, t_malloc *new)
{
    t_malloc    *current;

    if (!*lst || !lst)
    {
        lst = &new;
        return ;
    }
    current = *lst;
    while (current->next != NULL)
    {
        current = current->next;

    }
    current->next = new;
}

void ft_mallocclear(t_malloc **st)
{
    t_malloc *tmp;
    t_malloc *lst;
    lst = *st;

    // Ensure the list and its content exist
    if (!lst)
        return;

    // Iterate through the list and free the nodes
    while (lst)
    {
        tmp = lst->next;  // Save the next node
        if (lst->ptr)
        {
            printf("\n#####%p#####\n", lst->ptr);
            free(lst->ptr);  // Free the memory pointed to by ptr
        }
        free(lst);  // Free the node itself
        lst = tmp;  // Move to the next node
    }
    lst = NULL;  // Ensure the list pointer is set to NULL after clearing
}

void    *c_malloc(size_t size, int flag)
{
    static t_malloc    *head;
    t_malloc            *tmp;
    void            *ptr;

    if (flag == 1)
    {
        ptr = malloc(size);
        if (!ptr)
            return (ft_mallocclear(&head), NULL);
        tmp = ft_mallocnew(ptr);
        if (!tmp)
            return (ft_mallocclear(&head), free(ptr), NULL);
        ft_mallocadd_back(&head, tmp);
        return (ptr);
    }
    else if (flag == 0)
	{
		// printf("\n\n#####%p#####\n",&head);
        ft_mallocclear(&head);
		printf("%d\n",flag);
	}
    return (NULL);
}
