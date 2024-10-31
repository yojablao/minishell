/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:14:10 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/31 15:19:28 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expanding_values(char *key, t_env *env)
{
	t_env	*tmp;
	char	*value;

	tmp = env;
	if (key[0] >= '0' && key[0] <= '9')
		return (f_strdup(key + 1));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key) && env->flage == 0)
		{
			value = f_strdup(tmp->value);
			return (value);
		}
		if (!ft_strcmp(tmp->key, key) && env->flage == 1)
		{
			value = f_strdup(f_remove_spaces(tmp->value));
			return (value);
		}
		tmp = tmp->next;
	}
	return (f_strdup(""));
}

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

char	*join_buffer(char *tmp, int *j, int start, char *buffer)
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

char	*handle_d_q_util(char *tmp, int *j, t_env *env, char *buffer)
{
	char	*value;
	char	*key;

	if (tmp[*j] == '$' && tmp[*j + 1] == '?')
	{
		value = ft_itoa(get_exit(0, 1));
		(*j)++;
		buffer = f_strjoin(buffer, value);
	}
	else if (tmp[*j] == '$' && special_letter(tmp[*j + 1]) == false)
	{
		key = get_key(tmp + (*j));
		(*j) += ft_strlen(key) - 1;
		env->flage = 0;
		value = expanding_values(key + 1, env);
		buffer = f_strjoin(buffer, value);
	}
	return (buffer);
}

char	*handle_d_q_content(char *tmp, int *j, t_env *env, char *buffer)
{
	int		start;

	if ((tmp[*j] == '$' && tmp[*j + 1] == '?')
		|| (tmp[*j] == '$' && special_letter(tmp[*j + 1]) == false))
		buffer = handle_d_q_util(tmp, j, env, buffer);
	else if (tmp[*j] == '$' && special_letter(tmp[*j + 1]) == true)
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
