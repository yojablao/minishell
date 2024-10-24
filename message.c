/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:12:57 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/23 16:56:57 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strrange(char *s, int start, int end)
{
	int		i;
	char	*str;

	str = master(end - start + 1,1);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
    str[i] = '\0';
	return (str);
}
bool	special_letter(char l)
{
	char	*s;
	int		i;

	i = 0;
    if (l == 0)
        return true;
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
	int			i;
    int         start;
    int         end;
	char		*str;

	i = 0;
	end = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = i++;
			while (s[i] && !special_letter(s[i]) && s[i] != '$' && s[i] != '\'' && s[i] != '\"')
				i++;
			end = i;
			break ;
		}
		i++;
	}
	str = ft_strrange(s, start, end);
	return (str);
}
char *expand_exit_status(int status)
{
    char *str;

    str = ft_itoa(status);
    return (str);
}
char *expanding_valuess(char *key, t_env *env)
{
    t_env *tmp;
    char *value;

    tmp = env;
    if (key[0] >= '0' && key[0] <= '9')
        return (f_strdup(key + 1));
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
        {
            value = f_strdup(tmp->value);
            return (value);
        }
        tmp = tmp->next;
    }
    return (f_strdup(""));
}
int checkexpand(char *s)
{
    int i = 0;
    while(s[i])
    {
        if(s[i]== '$')
            return 1;
        i++;
    }
    return 0;
}
char *ft_expand1(char *s, char **envi)
{
    int i = 0;
    int end;
    int start;
    char *buffer = NULL;
    char *tmp;
    char *value;
    char *key;
    t_env *env;

    env = env_set(envi);
    while (s[i])
    {
        if (s[i] == '\'')
        {
            start = i++;
            while (s[i] && s[i] != '\'')
                i++;
            end = i;
            tmp = ft_strrange(s, start + 1, end);
            buffer= f_strjoin(buffer, tmp);
            
        }
        else if (s[i] == '\"')
        {
            if (s[i + 1] == '\"')
                i++;
            else
            {
                start = i++;
                while (s[i] && s[i] != '\"')
                    i++;
                end = i--;
                tmp = ft_strrange(s, start + 1, end);
                if (checkexpand(tmp))
                {
                    int j = 0;
                    while (tmp[j])
                    {
                        if (tmp[j] == '$')
                        {
                        key = get_key(tmp + j);
                        j += ft_strlen(key) - 1;
                        value = expanding_valuess(key + 1, env);
                        buffer = f_strjoin(buffer, value);
                        }
                        else
                        {
                            start = j;
                            while (tmp[j] && tmp[j] != '$')
                                j++;
                            end = j--;
                            value = ft_strrange(tmp, start,end);
                            buffer = f_strjoin(buffer, value);
                        }
                        j++;
                    }
                }
                else
                    buffer = f_strjoin(buffer, tmp);
                i++;
            }
        }
        else if (s[i] == '$')
        {
            if (s[i + 1] == '$' || special_letter(s[i + 1]))
            {
                buffer = f_strjoin(buffer, ft_strdup("$"));
                i++;
            }
            else if (s[i + 1] == '?')
            {
                tmp = ft_itoa(get_exit(0,1));
                buffer = f_strjoin(buffer,tmp);
                free(tmp);
                i++;
            }else if (s[i + 1] == '\"' || s[i + 1] == '\'')
                i++;
            else
            {
                key = get_key(s + i);
                i += ft_strlen(key) - 1;
                tmp = expanding_valuess(key + 1, env);
                buffer = f_strjoin(buffer, tmp);
            }
        }
        else 
        {
            start = i;
            while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
                i++;
            tmp = ft_strrange(s, start, i);
            buffer = f_strjoin(buffer, tmp);
        }
        if (s[i])
            i++;
    }
    return (buffer);
}


char *ft_expand(char *s, char **env)
{
    char **array;
    char *result;

    array = NULL;
    result = NULL;
    array = f_split(s, ' ');
    int i = 0;
    while (array[i])
    {
        if (ft_strcmp(array[i], "<<") == 0)
        {
            result = f_strjoin(result, f_strdup(array[i]));
            result = f_strjoin(result, " ");
            result = f_strjoin(result, f_strdup(array[i + 1]));
            result = f_strjoin(result, " ");
            i++;
        }
        else
        {
            result = f_strjoin(result, ft_expand1(array[i], env));
            result = f_strjoin(result, " ");
        }
        i++;
    }
    return (result);
}

