/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:50:24 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/01 04:13:06 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*valid_exp(char *content, char *expanded, int status)
{
	if (status == -1 || status != 4)
		return (expanded);
	else
		return (f_strdup(content));
}

bool	empty_q(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}

void	filehandler(t_exec_cmd **s)
{
	if ((*s)->infd == -1 || (*s)->outfd == -1)
		exit(EXIT_FAILURE);
	if ((*s)->infd != 0 && (*s)->infd != -1)
	{
		if (dup2((*s)->infd, STDIN_FILENO) == -1)
		{
			exit(EXIT_FAILURE);
		}
		close((*s)->infd);
	}
	if ((*s)->outfd != 1 && (*s)->outfd != -1)
	{
		if (dup2((*s)->outfd, 1) == -1)
		{
			exit(EXIT_FAILURE);
		}
		close((*s)->outfd);
	}
}

void	f(void *content)
{
	char	*s;
	int		i;
	int		j;
	int		single_q;
	int		double_q;

	i = 0;
	j = 0;
	single_q = 0;
	double_q = 0;
	s = (char *)content;
	while (s[i])
	{
		if (s[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (s[i] == '"' && !single_q)
			double_q = !double_q;
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}
