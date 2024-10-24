/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:12:57 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/25 00:11:57 by yojablao         ###   ########.fr       */
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
//////////Handle empty double quotes ("") directly (which you already do), but there are potential edge cases when quotes are misaligned or nested.
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
// bool valid_env_char(char c)
// {
//     return (ft_isalnum(c) || c == '_');
// }
char	*get_key(char *s)
{
	// t_env	e;
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
char *f_remove_spaces(char *str)
{
    int i;
    char *res;
    char *value;
    int start;
    int need_space;

    res = NULL;
    i = 0;
    need_space = 0;

    // Skip leading spaces
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;

    while (str[i])
    {
        // If we need a space and there's more content ahead
        if (need_space == 1 && str[i] != ' ' && str[i] != '\t' && res != NULL)
            res = f_strjoin(res, f_strdup(" "));

        // Get the word
        start = i;
        while (str[i] && str[i] != ' ' && str[i] != '\t')
            i++;
        value = ft_strrange(str, start, i);
        res = f_strjoin(res, value);

        // Skip consecutive spaces
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;

        // Set flag to add space before next word
        need_space = (str[i] != '\0');
    }
    printf("res [%s]\n",res);
    return (res);
}

char *expanding_valuess(char *key, t_env *env, int flag)
{
    t_env *tmp;
    char *value;

    tmp = env;
    if (key[0] >= '0' && key[0] <= '9')
        return (f_strdup(key + 1));
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key) && flag == 0)
        {
            value = f_strdup(tmp->value);
            return (value);
        }
        if (!ft_strcmp(tmp->key, key) && flag == 1)
        {
            value = f_strdup(f_remove_spaces(tmp->value));
            return(value);
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
// char *ft_expand1(char *s, char **envi)
// {
//     int i = 0;
//     int end;
//     int start;
//     char *buffer = NULL;
//     char *tmp;
//     char *value;
//     char *key;
//     t_env *env;

//     env = env_set(envi);
//     while (s[i])
//     {
//         if (s[i] == '\'')
//         {
//             start = i++;
//             while (s[i] && s[i] != '\'')
//                 i++;
//             end = i;
//             tmp = ft_strrange(s, start + 1, end);
//             buffer= f_strjoin(buffer, tmp);
//         }
//         else if (s[i] == '\"')
//         {
//             if (s[i + 1] == '\"')
//                 i++;
//             else
//             {
//                 start = i++;
//                 while (s[i] && s[i] != '\"')
//                     i++;
//                 end = i--;
//                 tmp = ft_strrange(s, start + 1, end);
//                 if (checkexpand(tmp))
//                 {
//                     int j = 0;
//                     while (tmp[j])
//                     {
//                         if (tmp[j] == '$' && special_letter(tmp[j + 1]) == false)
//                         {
//                         key = get_key(tmp + j);
//                         j += ft_strlen(key) - 1;
//                         value = expanding_valuess(key + 1, env);
//                         buffer = f_strjoin(buffer, value);
//                         printf("here\n");
//                         }
//                         else if (tmp[j] == '$' && special_letter(tmp[j + 1]) == true)
//                         {
//                             start = j;
//                             j++;
//                             while (tmp[j] && tmp[j] != '$')
//                                 j++;
//                             end = j--;
//                             value = ft_strrange(tmp, start,end);
//                             buffer = f_strjoin(buffer, value);
//                         }
//                         else
//                         {
//                             start = j;
//                             while (tmp[j] && tmp[j] != '$')
//                                 j++;
//                             end = j--;
//                             value = ft_strrange(tmp, start,end);
//                             buffer = f_strjoin(buffer, value);
//                         }
//                         j++;
//                     }
//                 }
//                 else
//                     buffer = f_strjoin(buffer, tmp);
//                 i++;
//             }
//         }
//         else if (s[i] == '$')
//         {
//             if (s[i + 1] == '$')
//             {
//                 buffer = f_strjoin(buffer, ft_strdup("$"));
//                 i++;
//             }
//             else if (special_letter(s[i + 1]) == true)
//             {
//                 start = i;
//                 i++;
//                 while(s[i] && s[i] != '$' && s[i] != '\'' && s[i] != '"')
//                     i++;
//                 end = i--;
//                 value = ft_strrange(s, start,end);
//                 buffer = f_strjoin(buffer, value);
//             }
//             else if (s[i + 1] == '?')
//             {
//                 tmp = ft_itoa(get_exit(0,1));
//                 buffer = f_strjoin(buffer,tmp);
//                 free(tmp);
//                 i++;
//             }
//             else
//             {
//                 key = get_key(s + i);
//                 i += ft_strlen(key) - 1;
//                 tmp = expanding_valuess(key + 1, env);
//                 buffer = f_strjoin(buffer, tmp);
//             }
//         }
//         else 
//         {
//             start = i;
//             while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
//                 i++;
//             end = i--;
//             tmp = ft_strrange(s, start, end);
//             buffer = f_strjoin(buffer, tmp);
//         }
//         if (s[i])
//             i++;
//     }
//     if (buffer[0] == 0)
//         return (NULL);
//     return (buffer);
// }

//---------------------------------//
// Handle simple quote expansion

char *handle_single_quote(char *s, int *i, char *buffer)
{
    int start;
    int end;
    char *tmp;

    start = (*i)++;
    printf("start -> %d\n",start);
    while (s[*i] && s[*i] != '\'')
        (*i)++;
    end = *i;
    printf("end -> %d\n",end);
    tmp = ft_strrange(s, start + 1, end);
    return (f_strjoin(buffer, tmp));
}

char	*join_buffer(char *tmp, int *j, int start)
{
	char	*value;
	char	*buffer;
	int		end;

	buffer = NULL;
	while (tmp[*j] && tmp[*j] != '$')
		(*j)++;
	end = (*j)--;
	value = ft_strrange(tmp, start, end);
	buffer = f_strjoin(buffer, value);
	return (buffer);
}

char *handle_double_quote_content(char *tmp, int *j, t_env *env, char *buffer)
{
    char *key;
    char *value;
    int start;

    if (tmp[*j] == '$' && special_letter(tmp[*j + 1]) == false)
    {
        key = get_key(tmp + (*j));
        (*j) += ft_strlen(key) - 1;
        value = expanding_valuess(key + 1, env, 0);
        buffer = f_strjoin(buffer, value);
    }
    else if (tmp[*j] == '$' && special_letter(tmp[*j + 1]) == true)
    {
		start = *j;
		(*j)++;
        buffer = join_buffer(tmp, j, start);
    }
    else
    {
        start = *j;
		buffer = join_buffer(tmp, j, start);
    }
    return (buffer);
}

char *process_double_quote(char *tmp, t_env *env, char *buffer)
{
    int j;

    j = 0;
    while (tmp[j])
    {
        buffer = handle_double_quote_content(tmp, &j, env, buffer);
        j++;
    }
    return (buffer);
}

char *handle_double_quote(char *s, int *i, t_env *env, char *buffer)
{
    int start;
    int end;
    char *tmp;

    if (s[*i + 1] == '\"')
        return ((*i)++, buffer);
    start = (*i)++;
    while (s[*i] && s[*i] != '\"')
        (*i)++;
    end = (*i)--;
    tmp = ft_strrange(s, start + 1, end);
    //printf("tmp ;%s;\n",tmp);
    if (checkexpand(tmp))
        {
            buffer =  process_double_quote(tmp, env, buffer);
        }
    else
        buffer = f_strjoin(buffer, tmp);
    return (buffer);
}

char *handle_dollar_special(char *s, int *i, char *buffer)
{
    char *tmp;

    if (s[*i + 1] == '$')
        return ((*i)++, f_strjoin(buffer, ft_strdup("$")));
    if (s[*i + 1] == '?')
    {
        tmp = ft_itoa(get_exit(0, 1));
        buffer = f_strjoin(buffer, tmp);
        free(tmp);
        return ((*i)++, buffer);
    }
    return (buffer);
}

char *handle_dollar(char *s, int *i, t_env *env, char *buffer)
{
    int start;
    int end;
    char *tmp;
    char *key;
    char *value;

    if (s[*i + 1] == '$' || s[*i + 1] == '?')
        return (handle_dollar_special(s, i, buffer));
    if (special_letter(s[*i + 1]) == true)
    {
        start = (*i)++;
        while(s[*i] && s[*i] != '$' && s[*i] != '\'' && s[*i] != '"')
            (*i)++;
        end = (*i)--;
        value = ft_strrange(s, start, end);
        return (f_strjoin(buffer, value));
    }
    key = get_key(s + *i);
    *i += ft_strlen(key) - 1;
    tmp = expanding_valuess(key + 1, env, 1);
    return (f_strjoin(buffer, tmp));
}

char *handle_normal_text(char *s, int *i, char *buffer)
{
    int start;
    int end;
    char *tmp;

    start = *i;
    while (s[*i] && s[*i] != '\'' && s[*i] != '\"' && s[*i] != '$')
        (*i)++;
    end = (*i)--;
    tmp = ft_strrange(s, start, end);
    return (f_strjoin(buffer, tmp));
}

char *ft_expand1(char *s, char **envi)
{
    int i;
    char *buffer;
    t_env *env;

    i = 0;
    buffer = NULL;
    env = env_set(envi);
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
    if (buffer && buffer[0] == 0)
        return (NULL);
    return (buffer);
}