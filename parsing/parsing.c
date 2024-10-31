/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 12:28:48 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_count(t_list *a)
{
	int	i;

	i = 0;
	while (a)
	{
		if (a->stat == 4)
			i++;
		a = a->next;
	}
	return (i);
}

static int	pipe_check(t_list *a)
{
	int	i;

	i = 0;
	while (a)
	{
		if (a->stat == 0)
			i++;
		a = a->next;
	}
	return (i);
}

static int	heredoc_pipe_check(t_shell *sh)
{
	if (heredoc_count(sh->a) > 16)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		exit(2);
	}
	sh->n_pipe = pipe_check(sh->a);
	if (sh->n_pipe > 1390)
		return (ft_putstr_fd("bash: fork: Resource temporarily unavailable\n",
				2), -1);
	return (0);
}

int	parsing_input(t_shell **cmd, char *input)
{
	if (!syntax(input, cmd))
		return (get_exit(258, 0), printf("syntax error\n"), -1);
	(*cmd)->cmd = aloc_comond((*cmd)->cmd);
	(*cmd)->head = (*cmd)->cmd;
	if (!(*cmd)->cmd || !(*cmd)->a)
		return (-1);
	(*cmd)->head = (*cmd)->cmd;
	if (heredoc_pipe_check(*cmd) == -1)
		return (-1);
	if ((*cmd)->n_pipe > 0)
	{
		if (init_pipe_line(cmd) == false)
			return (-1);
		(*cmd)->cmd = (*cmd)->head;
		return (2);
	}
	else
	{
		if (comond_init(cmd) == false)
			return (-1);
		return (1);
	}
}
