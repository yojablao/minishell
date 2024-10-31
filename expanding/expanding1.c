/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:12:57 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/31 15:13:25 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_double_quote(char *s, int *i, t_env *env, char *buffer)
{
	int		start;
	int		end;
	char	*tmp;

	if (s[*i + 1] == '\"')
		return ((*i)++, buffer);
	start = (*i)++;
	while (s[*i] && s[*i] != '\"')
		(*i)++;
	end = (*i)--;
	(*i)++;
	tmp = ft_strrange(s, start + 1, end);
	if (checkexpand(tmp))
		buffer = process_double_quote(tmp, env, buffer);
	else
		buffer = f_strjoin(buffer, tmp);
	return (buffer);
}

char	*handle_dollar_special(char *s, int *i, char *buffer)
{
	char	*tmp;

	tmp = NULL;
	if (s[*i + 1] == '$')
		return ((*i)++, f_strjoin(buffer, f_strdup("$")));
	if (s[*i + 1] == '?')
	{
		tmp = ft_itoa(get_exit(0, 1));
		buffer = f_strjoin(buffer, tmp);
		free(tmp);
		return ((*i)++, buffer);
	}
	return (buffer);
}

char	*handle_dollar(char *s, int *i, t_env *env, char *buffer)
{
	char	*value;
	char	*tmp;
	char	*key;
	int		start;
	int		end;

	if (s[*i + 1] == '$' || s[*i + 1] == '?')
		return (handle_dollar_special(s, i, buffer));
	if (special_letter(s[*i + 1]) == true)
	{
		start = (*i)++;
		while (s[*i] && s[*i] != '$' && s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		end = (*i)--;
		value = ft_strrange(s, start, end);
		return (f_strjoin(buffer, value));
	}
	key = get_key(s + *i);
	*i += ft_strlen(key) - 1;
	env->flage = 1;
	tmp = expanding_values(key + 1, env);
	return (f_strjoin(buffer, tmp));
}

char	*handle_normal_text(char *s, int *i, char *buffer)
{
	char	*tmp;
	int		start;
	int		end;

	tmp = NULL;
	start = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '\"' && s[*i] != '$')
		(*i)++;
	end = (*i)--;
	tmp = ft_strrange(s, start, end);
	return (f_strjoin(buffer, tmp));
}

char	*ft_expand1(char *s, char **envi, t_env *lenv)
{
	t_env	*env;
	char	*buffer;
	int		i;

	i = 0;
	buffer = NULL;
	env = env_set(envi);
	env->flage = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			buffer = handle_single_quote(s, &i, buffer);
		else if (s[i] == '\"')
			buffer = handle_double_quote(s, &i, env, buffer);
		else if (s[i] == '$')
			buffer = handle_dollar(s, &i, env, buffer);
		else
			buffer = handle_normal_text(s, &i, buffer);
		if (s[i])
			i++;
	}
	lenv->flage = env->flage;
	if (buffer && !*buffer)
		return (NULL);
	return (buffer);
}
