/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandingtools1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:17:50 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/04 16:41:54 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrange(char *s, int start, int end)
{
	int		i;
	char	*str;

	str = master(end - start + 1, 1);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

bool	special_lt(char l)
{
	char	*s;
	int		i;

	i = 0;
	if (l == 0)
		return (true);
	s = "=/*-+@!#%^.*:";
	if (l == ' ' || (l >= 9 && l <= 13))
		return (true);
	while (s[i])
	{
		if (s[i] == l)
			return (true);
		i++;
	}
	return (false);
}

char	*get_key(char *s)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	i = 0;
	end = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = i++;
			while (s[i] && !special_lt(s[i])
				&& s[i] != '$' && s[i] != '\'' && s[i] != '\"')
				i++;
			end = i;
			break ;
		}
		i++;
	}
	str = ft_strrange(s, start, end);
	return (str);
}

char	*ft_check_operator(char	*value, char *res)
{
	if (!value)
		return (NULL);
	if (!ft_strcmp(value, "<<") || !ft_strcmp(value, ">>")
		|| !ft_strcmp(value, "<") || !ft_strcmp(value, ">")
		|| !ft_strcmp(value, "|"))
	{
		res = f_strjoin(res, f_strdup("\""));
		res = f_strjoin(res, value);
		res = f_strjoin(res, f_strdup("\""));
	}
	else
		res = f_strjoin(res, value);
	return (res);
}

char	*f_remove_spaces(char *str)
{
	char	*value;
	char	*res;
	int		need_space;
	int		start;
	int		i;

	res = NULL;
	i = 0;
	need_space = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		if (need_space == 1 && str[i] != ' ' && str[i] != '\t' && res != NULL)
			res = f_strjoin(res, f_strdup(" "));
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
		value = ft_strrange(str, start, i);
		res = ft_check_operator(value, res);
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		need_space = (str[i] != '\0');
	}
	return (res);
}
