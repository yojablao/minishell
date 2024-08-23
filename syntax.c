/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 01:04:07 by hamrachi          #+#    #+#             */
/*   Updated: 2024/08/23 23:44:08 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	zero_one(int *c)
{
	if (*c == 0)
		*c = 1;
	else
		*c = 0;
}

int	ft_check_quotes(char *str)
{
	t_quotes	quote;

	quote.i = 0;
	quote.dq = 0;
	quote.q = 0;

	while (str[quote.i])
	{
		if (str[quote.i] == 34 && quote.q == 0)
			zero_one(&quote.dq);
		if (str[quote.i] == 39 && quote.dq == 0)
			zero_one(&quote.q);
		quote.i++;
	}
	if (quote.q == 0 && quote.dq == 0)
		return (1);
	else
		return (0);
}

void	skip_betw_quotes(char *str, size_t *i)
{
	if (str[*i] == 34)
	{
		(*i)++;
		while (str[*i] != 34)
			(*i)++;
	}
	if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] != 39)
			(*i)++;
	}
}
size_t	ft_strlen_spaces(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			skip_betw_quotes(str, &i);
			i++;
		}
		if (str[i] == '|')
			j += 1;
		if (str[i] == '<' && str[i - 1] != '<' && str[i + 1] != '<')
			j += 1;
		if (str[i] == '>' && str[i - 1] != '>' && str[i + 1] != '>')
			j += 1;
		if (str[i] == '<' && str[i + 1] == '<')
			j += 1;
		if (str[i] == '>' && str[i + 1] == '>')
			j += 1;
		i++;
	}
	return (j);
}

void	add_spaces(char c, char *new, size_t *j, int v)
{
	if (v == 0)
	{
		new[*j] = ' ';
		(*j)++;
		new[*j] = c;
		(*j)++;
		new[*j] = ' ';
		(*j)++;
	}
	else
	{
		new[*j] = ' ';
		(*j)++;
		new[*j] = c;
		(*j)++;
		new[*j] = c;
		(*j)++;
		new[*j] = ' ';
		(*j)++;
	}
}

void	full_betw_quotes(char *str, char *new, size_t *j, size_t *i)
{
	if (str[*i] == 34)
	{
		new[(*j)] = 34;
		(*j)++;
		while(str[*i])
		{
			if (str[*i] == 34)
				break;
			new[(*j)++] = str[*i];
			(*i)++;
		}
		new[(*j)] = 34;
	}
	else if (str[*i] == 39)
	{
		while(str[*i])
		{
			if (str[*i] == 39)
				break;
			new[(*j)++] = str[*i];
			(*i)++;
		}
		new[(*j)] = 39;
	}
}
char	*ft_correct_line(char *str)
{
	char	*new;
	t_correc	ind;

	new = ft_my_malloc((ft_strlen(str) + (ft_strlen_spaces(str)) * 2));
	printf("allocate -> %lu\n",(ft_strlen(str) + (ft_strlen_spaces(str) * 2)));
	ind.j = 0;
	ind.i = 0;
	while (str[ind.i])
	{
		if (str[ind.i] == 39 || str[ind.i] == 34)
		{
		//TODO full_betw_quotes(str, new, &ind.j, &ind.i);
			ind.i++;
		}
		if (((str[ind.i] == '<' && str[ind.i + 1] == '<')
				|| (str[ind.i] == '>' && str[ind.i + 1] == '>')))
			{
				add_spaces(str[ind.i], new, &ind.j, 1);
				ind.i++;
			}
		else if ((str[ind.i] == '|' || (str[ind.i] == '<' && str[ind.i + 1] != '<')
				|| (str[ind.i] == '>' && str[ind.i + 1] != '>')))
				add_spaces(str[ind.i], new, &ind.j, 0);
		else
				new[ind.j++] = str[ind.i];
		ind.i++;
	}
	return (new);
}
int	ft_position_para(char	*str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[0] ==  '|' || str[0] == '<' || str[0] == '>')
			return (0);
		if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
			return (0);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && str[i + 1] == '\0')
			return (0);
		if (str[i - 1] == '<' && str[i] == '<' && str[i + 1] == '\0')
			return (0);
		if (str[i - 1] == '>' && str[i] == '>' && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}
int	ft_skip_spaces(char *str)
{
	//printf("1 new str %s\n", str);
	while (*str)
	{
		if (*str != ' ')
			break;
		str++;
	}
	if (*str == '|' || *str == '>' || *str == '<')
		return (0);
	//printf("2 new str %s\n", str);
	return (1);
}
int	ft_rank_para(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && ft_skip_spaces(&str[i + 1]) == 0)
			return (0);
		if (str[i] == '>' && str[i + 1] != '>')
		{
			if (ft_skip_spaces(&str[i + 1]) == 0)
				return (0);
		}
		if (str[i] == '<' && str[i + 1] != '<')
		{
			if (ft_skip_spaces(&str[i + 1]) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
int	syntax_ok(char *str)
{
	if (ft_check_quotes(str) == 0)
		return (0);
	if (ft_position_para(str) == 0)
		return (0);
	if (ft_rank_para(str) == 0)
		return (0);
	printf("%s\n", ft_correct_line(str));
	//printf("%zu\n", ft_strlen_spaces(str));
	return (1);
}
// just correct  line with space and  respect no space if tokens inside " | << >> < >";
/*
char l = s[i++];
while(s[i])
	if (s[i++] == l)
		break;
*/