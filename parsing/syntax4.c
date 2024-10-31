/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:30:45 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 12:31:39 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = -1;
	c = 0;
	while (str[++i])
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
	}
	return (c * 2);
}
