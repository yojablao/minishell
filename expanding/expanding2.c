/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:14:10 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/01 00:48:34 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_single_quote(char *s, int *i, char *buffer)
{
	int		start;
	int		end;
	char	*tmp;

	start = (*i)++;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	end = *i;
	tmp = ft_strrange(s, start + 1, end);
	return (f_strjoin(buffer, tmp));
}

char	*join_buffer(char *tmp, int *j, int start, char	*buffer)
{
	char	*value;
	int		end;

	value = NULL;
	while (tmp[*j] && tmp[*j] != '$')
		(*j)++;
	end = (*j)--;
	value = ft_strrange(tmp, start, end);
	buffer = f_strjoin(buffer, value);
	return (buffer);
}

char	*get_buffer(char *tmp, int *j, t_env *env, char *buffer)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	env->flage = 0;
	key = get_key(tmp + (*j));
	(*j) += ft_strlen(key) - 1;
	value = expanding_values(key + 1, env);
	buffer = f_strjoin(buffer, value);
	return (buffer);
}

char	*handle_d_q_content(char *tmp, int *j, t_env *env, char *buffer)
{
	char	*value;
	int		start;

	value = NULL;
	if (tmp[*j] == '$' && tmp[*j + 1] == '?')
	{
		value = ft_itoa(get_exit(0, 1));
		buffer = f_strjoin(buffer, value);
		(*j)++;
	}
	else if (tmp[*j] == '$' && !special_lt(tmp[*j + 1]) && tmp[*j + 1] != '\'')
		buffer = get_buffer(tmp, j, env, buffer);
	else if ((tmp[*j] == '$' && special_lt(tmp[*j + 1]))
		|| (tmp[*j] == '$' && tmp[*j + 1] == '\''))
	{
		start = *j;
		(*j)++;
		buffer = join_buffer(tmp, j, start, buffer);
	}
	else
	{
		start = *j;
		buffer = join_buffer(tmp, j, start, buffer);
	}
	return (buffer);
}

char	*process_double_quote(char *tmp, t_env *env, char *buffer)
{
	int	j;

	j = 0;
	while (tmp[j])
	{
		buffer = handle_d_q_content(tmp, &j, env, buffer);
		j++;
	}
	return (buffer);
}
