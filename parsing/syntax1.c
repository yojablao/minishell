/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:46:07 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/26 08:54:54 by yojablao         ###   ########.fr       */
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
char	*skip_betw_quotes2(char *str)
{
	if (*str == 34)
	{
		str++;
		while (*str && *str != 34)
			str++;
	}
	else if (*str == 39)
	{
		str++;
		while (*str && *str != 39)
			str++;
	}
	return (str);
}
size_t	skip_betw_quotes3(char *str, size_t *i)
{
	char	quote_char;
	size_t	len;

	quote_char = str[*i];
	len = 0;
	len++;
	(*i)++;
	while (str[*i] && str[*i] != quote_char)
	{
		len++;
		(*i)++;
	}
	len++;
	return (len);
}

size_t	ft_count_operators(char *str)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			skip_betw_quotes(str, &i);
		else if (str[i] == '|')
			c++;
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			c++;
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			c++;
		}
		i++;
	}
	return (c * 2);
}

char	*ft_handel_spaces_allocation(char *str)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = NULL;
	len2 = ft_count_operators(str);
	len1 = ft_strlen(str) + len2;
	new = ft_my_malloc(len1 + 1);
	return (new);
}

int	ft_check_quotes(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			skip_betw_quotes(str, &i);
			if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}
void	ft_write_bet_quotes(char *str, char *new, int *i, int *j)
{
	char	l;

	l = str[*i];
	new[(*j)++] = str[(*i)++];
	while (str[*i])
	{
		if (str[*i] == l)
			break ;
		new[(*j)++] = str[(*i)++];
	}
	new[(*j)++] = str[(*i)];
}

void	add_spaces(char c, char *new, int *j, int v)
{
	if (v == 0)
	{
		new[(*j)++] = ' ';
		new[(*j)++] = c;
		new[(*j)++] = ' ';
	}
	else
	{
		new[(*j)++] = ' ';
		new[(*j)++] = c;
		new[(*j)++] = c;
		new[(*j)++] = ' ';
	}
}

void	ft_add_spaces(char *str, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			ft_write_bet_quotes(str, new, &i, &j);
		else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
				+ 1] == '>'))
			add_spaces(str[i++], new, &j, 1);
		else if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>'))
			add_spaces(str[i], new, &j, 0);
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
}

int	ft_check_her(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
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
	while (s[i])
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
/*
split ("|");0 done;
char **allcmd == echo $DFdf > $USER
char	**cmd = echo \0
char	**red = > file > hamrachi
*/