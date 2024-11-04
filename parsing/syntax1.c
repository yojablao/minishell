/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:46:07 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/04 17:51:04 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_betw_quotes(char *str, size_t *i)
{
	char	quot_char;

	quot_char = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quot_char)
		(*i)++;
}

int	ft_check_her(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			skip_betw_quotes(str, &i);
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (0);
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0);
		i++;
	}
	return (1);
}

char	*rm_escap_char(char *s)
{
	int		i;
	int		j;
	int		single_q;
	int		double_q;
	char	*res;

	i = 0;
	j = 0;
	single_q = 0;
	double_q = 0;
	res = master(ft_strlen(s) + 1, 1);
	if (!res)
		return (NULL);
	while (s && s[i])
	{
		if (s[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (s[i] == '"' && single_q == 0)
			double_q = !double_q;
		else
			res[j++] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	syntax(char *str, t_shell **cmd)
{
	char	*new;
	char	*expend;

	new = NULL;
	expend = NULL;
	(*cmd)->a = NULL;
	if (!ft_check_quotes(str) || !ft_check_her(str))
		return (0);
	new = ft_handel_spaces_allocation(str);
	ft_add_spaces(str, new);
	ft_full_list(&(*cmd)->a, new, 32);
	if (ft_check_grammer((*cmd)->a) == 0)
		return (0);
	return (1);
}
