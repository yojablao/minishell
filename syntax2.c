/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:15:24 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/26 05:35:43 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_full_list(t_list **a, char *s , int c)
{
	char	**array;
	t_list	*tmp;
	int		i;

	array = ft_split(s, c);
	if (!array)
		exit(1);
	i = 0;
	while (i < ft_counter(s, c))
	{
		printf("this is array = %s\n",array[i]);
		i++;
	}
	i = 0;
	while (array[i])
	{
		tmp = ft_lstnew(array[i]);
		// printf("==> %s\n", tmp->content);
		// printf("stat ==> %d\n", tmp->stat);
		if (!tmp)
			exit(1);
		ft_lstadd_back(a, tmp);
		i++;
	}
	// ft_free_array(array);
}

void	ft_print_stack(t_exec_cmd *a)
{
    t_exec_cmd *tmp;

    tmp = a;
	int i = -1;
    while (tmp != NULL)
    {
		i = -1;
       printf("content ==> %s\n", tmp->cmd);
	   while (tmp->args[++i])
    		printf("args ==> %s\n", tmp->args[i]);

        tmp = tmp->next;
    }
}

void	ft_free_stack(t_list *a)
{
	t_list	*tmp;
	t_list	*to_free;

	tmp = a;
	while (tmp)
	{
		to_free = tmp -> next;
		free(tmp);
		tmp = to_free;
	}
	a = NULL;
}

int	ft_check_grammer(t_list *a)
{
	t_list *tmp;

	tmp = a;
	if (tmp -> stat == PIPE || !tmp)
			return(0);
	while(tmp)
	{
		if (tmp && tmp -> stat != TEXT && !tmp -> next)
			return(0);
		if(tmp -> stat != TEXT && tmp -> stat != PIPE)
		{
			if (tmp -> next && tmp -> next -> stat != TEXT)
				return (0);
		}
		if (tmp -> stat == PIPE)
		{
			if (tmp -> next && tmp -> next -> stat == PIPE)
				return (0);
		}
		tmp = tmp -> next;
	}
	return(1);
}


