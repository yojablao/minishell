/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:12:57 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/21 22:58:15 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int get_exit(int sts, bool set)
// {
//     static int status;
//     if (!set)
//         status = sts;
//     return (status);  
// }

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
            // printf("tmp:%s\n", tmp);
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

//     if(!s)
//         return(NULL);
//     env = env_set(envi);
//     while (s[i])
//     {
//         printf("%s\n",buffer);
//         if (s[i] == '\'')
//         {
//             start = i++;
//             while (s[i] && s[i] != '\'')
//                 i++;
//             end = i;
//             tmp = ft_strrange(s, start + 1, end);
//             // printf("tmp:%s\n", tmp);
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
//                         if (tmp[j] == '$')
//                         {
//                         key = get_key(tmp + j);
//                         j += ft_strlen(key) - 1;
//                         value = expanding_valuess(key + 1, env);
//                         buffer = f_strjoin(buffer, value);
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
//             if (s[i + 1] == '$' || special_letter(s[i + 1]))
//             {
//                 buffer = f_strjoin(buffer, ft_strdup("$"));
//                 i++;
//             }
//             else if (s[i + 1] == '?')
//             {
//                 tmp = ft_itoa(get_exit(0,1));
//                 buffer = f_strjoin(buffer,tmp);
//                 // free(tmp);
//                 i++;
//             }else if (s[i + 1] == '\"' || s[i + 1] == '\'')
//                 i++;
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
//             tmp = ft_strrange(s, start, i--);
//             buffer = f_strjoin(buffer, tmp);
//         }
//         i++;
//     }
//     return (buffer);
// }


// char *ft_expand(char *s, char **env)
// {
//     char **array;
//     char *result;

//     array = NULL;
//     result = NULL;
//     array = f_split(s, ' ');
//     int i = 0;
//     while (array[i])
//     {
//         if (ft_strcmp(array[i], "<<") == 0)
//         {
//             result = f_strjoin(result, f_strdup(array[i]));
//             result = f_strjoin(result, " ");
//             result = f_strjoin(result, f_strdup(array[i + 1]));
//             result = f_strjoin(result, " ");
//             i++;
//         }
//         else
//         {
//             result = f_strjoin(result, ft_expand1(array[i], env));
//             result = f_strjoin(result, " ");
//         }
//         i++;
//     }
//     return (result);
// }


//--------------------------------mine----------------------------/

// void skip_value(char *str, size_t *i)
// {
//     while (str[*i])
//     {
//         if (str[*i] == 34 || str[*i] == 39)
//             break;
//         (*i)++;
//     }
//     (*i)--;
// }
// size_t skip_value2(char *str, size_t *i)
// {
//     size_t len;
//     len = 0;
//     while (str[*i])
//     {
//         if (str[*i] == 34 || str[*i] == 39)
//             break;
//         len++;
//         (*i)++;
//     }
//     (*i)--;
//     return (len);
// }

// int ft_word_counter(char *str)
// {
//     size_t i;
//     size_t w;

//     i = 0;
//     w = 0;
//     while (str[i])
//     {
//         // printf();
//         if (str[i] == 34 || str[i] == 39)
//         {
//             skip_betw_quotes(str, &i);
//             w++;
//         }
//         else
//         {
//             skip_value(str, &i);
//             w++;
//         }
//         i++;
//     }
//     return (w);
// }
// char *f_substr(char *s, size_t start, size_t len)
// {
//     char *new;
//     size_t i;

//     if (!s)
//         return (NULL);
//     i = 0;
//     new = master(len + 1, 1);
//     if (!new)
//         return (NULL);
//     while (i < len)
//         new[i++] = s[start++];
//     new[i] = '\0';
//      //printf("subster == %s\n",new);
//     return (new);
// }

// char *ft_range(char *str, size_t *i, size_t start, size_t flag)
// {
//     size_t len;

//     len = 0;
//     if (flag == 0)
//         len = skip_betw_quotes3(str, i);
//     else
//         len = skip_value2(str, i);
//     return (f_substr(str, start, len));
// }

// char **ft_expanding_split(char *str)
// {
//     char **result;
//     int wc = ft_word_counter(str);
//     //printf("{%d}\n", wc);
//     size_t i;
//     size_t start;
//     size_t j;

//     result = (char **)f_calloc(wc + 1, sizeof(char *));
//     i = 0;
//     start = 0;
//     j = 0;
//     while (str[i])
//     {
//         if (str[i] == 34 || str[i] == 39)
//         {
//             start = i;
//             result[j] = ft_range(str, &i, start, 0);
//         }
//         else
//         {
//             start = i;
//             result[j] = ft_range(str, &i, start, 1);
//         }
//         i++;
//         j++;
//     }
//     result[j] = NULL;
//     return (result);
// }

// int ft_check_exist_charracter(char *s)
// {
//     int i = 0;
//     int v = 0;
//     int c = 0;

//     while (s[i])
//     {
//         if (s[i] == 34 || s[i] == 39)
//             v = 1;
//         if (s[i] == '$')
//             c = 1;
//         if (v == 1 && c == 1) // $ and quotes exist
//             return (3);
//         i++;
//     }
//     if (v == 0 && c == 1) // just $
//         return (1);
//     else if (v == 1 && c == 0) // just quotes
//         return (2);
//     else // no $ no quotes
//         return (0);
// }

// size_t ft_bring_index(char *s, char c)
// {
//     size_t i;

//     i = 0;
//     while (s[i])
//     {
//         if (s[i] == c && s[i + 1] != c)
//             return (i);
//         i++;
//     }
//     return (0);
// }

// int ft_check_next_charachter(char *s, size_t start, size_t len)
// {
//     if (s[len] == '\0')
//         return (0);
//     while (s[start])
//     {
//         if (start > len)
//         {
//             if (ft_isalnum(s[start]) == 1)
//                 return (1);
//             else
//                 return (0);
//         }
//         start++;
//     }
//     return (0);
// }

// size_t ft_check_special_char(char c)
// {
//     char *s;
//     int i = 0;

//     s = "$=/*-+\"\'@!#%^.*:";
//     while (s[i])
//     {
//         if (s[i] == c)
//             return (1);
//         i++;
//     }
//     return (0);
// }

// int ft_str_lencmp(char *s1, char *s2, size_t i)
// {
//     size_t j;
//     j = 0;
//     i++;

//     //printf("s1 %s\n",s1);
//     while (s1[i] && s2[j])
//     {
//         if (s1[i] - s2[j] == 0)
//         {
//             if (s2[j + 1] == '\0')
//             {
//                 return (-1);
//             }
//         }
//         else if (s1[i] - s2[i] != 0 && ft_check_special_char(s1[i]) == 1)
//             return (i);
//         else
//             break;
//         i++;
//         j++;
//     }
//     return (0);
// }

// char *ft_bring_key(char *s1, t_env *env, bool is_expand)
// {
//     size_t end;
//     t_env *tmp;
//     int r;
//     if (!s1)
//         return (NULL);
//     tmp = env;
//     /*
//         if (s1[0] == '$' && !s1[1])
//             return (f_strdup("$"));
//     */
//     if (s1[0] == '$' && !s1[1])
//         return (f_strdup("$"));
//     if (s1[0] == '$' && ft_isdigit(s1[1]) == 1)
//         return (f_substr(s1, 2, ft_strlen(s1)));
//     while (tmp)
//     {
//         r = ft_str_lencmp(s1, tmp->key, 0);
//         if (r == -1)
//         {
//              end = ft_strlen(tmp->key);
//             if (ft_check_next_charachter(s1, 0, end) == 0)
//             {
//                    if (ft_strlen(s1) > ft_strlen(tmp->key))
//                         return (f_strjoin(tmp->value, f_substr(s1, ft_strlen(tmp->key) + 1, ft_strlen(s1))));
//                     return (f_strdup(tmp->value));
//             }
//             else
//                 return(f_strdup(""));
//         }
//         else if (r > 0)
//             return (f_substr(s1, r, ft_strlen(s1)));
//         tmp = tmp->next;
//     }
//     return (f_strdup(""));
// }

// size_t ft_word_counter_by_dollar(char *str)
// {
//     size_t wrd;
//     size_t i;

//     i = 0;
//     wrd = 0;
//     if (str[0] != '$')
//         wrd++;
//     while (str[i])
//     {
//         if (str[i] == '$')
//             wrd++;
//         if ((str[i] == 39 || str[i] == 34 ) && (str[i + 1] == '$' || str[i + 1] == '\0'))
//             wrd++;
//         i++;
//     }
//     printf("wrd %zu\n", wrd);
//     return (wrd);
// }

// char **ft_split_by_dollar(char *s)
// {
//     char **result;
//     size_t wc;
//     size_t start;
//     size_t i;
//     size_t j;

//     wc = ft_word_counter_by_dollar(s);
//     result = (char **)f_calloc(wc + 1, sizeof(char *));
//     if (!result)
//         return (NULL);
//     i = 0;
//     j = 0;
//     while (s[i])
//     {
//         if (s[i] == '$')
//         {
//             start = i;
//             i++;
//             while (s[i] && s[i] != '$' && s[i] != 39 && s[i] != 34)
//                 i++;
//             result[j++] = f_substr(s, start, i - start);
//         }
//         else if (s[i] == 34 || s[i] == 39)
//         {
//             start = i;
//             while (s[i] && s[i] != '$')
//                 i++;
//             result[j++] = f_substr(s, start, i - start);
//         }
//         else
//         {
//             start = i;
//             while (s[i] && s[i] != '$')
//                 i++;
//             result[j++] = f_substr(s, start, i - start);
//         }
//     }
//     result[j] = NULL;
//     return (result);
// }

// char *ft_expend_just_dollar(char *s, t_env *env)
// {
//     char **array;
//     char *new;

//     (void)env;
//     new = NULL;
//     printf("hoho1\n");
//     array = ft_split_by_dollar(s);
    
//     int i = 0;
//     i = 0;
//     while (array[i])
//     {
//         printf("array = %s\n", array[i]);
//         i++;
//     }
//     i = 0;
//     while (array[i])
//     {
//         if (ft_check_exist_charracter(array[i]) == 0)
//         {
//             new = f_strjoin(new, array[i]);
//             // printf("new1--> %s\n",new);
//         }
//         else if (ft_check_exist_charracter(array[i]) == 2)
//             new = f_strjoin(new, array[i]);
//         else 
//         {
//             /*
//                 key = getkey(arry[i])
            
//                 if ()
//             */
//             new = f_strjoin(new, ft_bring_key(array[i], env, true));
//         }
//         i++;
//     }
//     printf("new2--> %s\n",new);
//     return (new);
// }

// char *f_expanding_quotes(void *content)
// {
//     char *s = (char *)content; // Cast content to char as it's passed as void *
//     int i = 0;
//     int j = 0;
//     int single_q = 0;
//     int double_q = 0;

//     while (s[i])
//     {
//         if (s[i] == '\'' && !double_q)
//             single_q = !single_q;
//         else if (s[i] == '"' && !single_q)
//             double_q = !double_q;
//         else
//             s[j++] = s[i]; // Copy valid characters to the current position
//         i++;
//     }
//     s[j] = '\0'; // Null-terminate at position j // hna
//     return (s);
// }
// char *f_check_is_expand(char *str, t_env *env)
// {
//     size_t i;
//     char *r;

//     if (str[0] == '"')
//         r = ft_expend_just_dollar(str, env);
//     else
//         return(f_expanding_quotes(str));
//     return(f_expanding_quotes(r));
// }

// void    ft_expanding(char *str,char **env)
// {
//     char **array;
//     char *result;
//     t_env *envi;
    
//     result = NULL;
//     envi = env_set(env);
//     //array2 = f_split(str, ' ');
//     array = ft_expanding_split(str);
//     int i = 0;
//     int j = 0;
//     while(array[i])
//     {
//         printf("first parsing ;%s;\n",array[i]);
//         i++;
//     }

//     while (array[i])
//     {
//          printf("resultglobal = %s\n",result);
//         if (ft_check_exist_charracter(array[i]) == 1)  // just $
//         {
//             printf("hiho0\n");
//             result = f_strjoin(result, ft_expend_just_dollar(array[i], envi));
//         }
//         else if (ft_check_exist_charracter(array[i]) == 2)  // just quotes
//         {
//             result = f_strjoin(result, f_expanding_quotes(array[i ]));
//              printf("result2 = %s\n",result);
//         }
//         else if (ft_check_exist_charracter(array[i]) == 3) // $ and quotes exist
//             {
//                 //result = f_check_is_expand(array[i], envi);
                
//                 result = f_strjoin(result,f_check_is_expand(array[i], envi));
//                 printf("result3 = %s\n",result);
//             }
//         else
//             result = f_strjoin(result, array[i]);
//         i++;
//     }
//     //if(!result)
//         printf("result = %s\n",result);
// }




// --------------------------------amine------------------------------//
// hjgl $isa /dF$ERgs"""FADS"$DS'''"dtfj$DSg ""     zxcv$HTH#$GFH#$DFH#$GDS$f

// FHKHJ"'''$USER$$USER'''"GHFGHJ$DFGHFGH
// char *getkey(char *s)
// {
//     char *str;
//     int i;
    
//     i = 0;
//     while (s[i])
//     {
//         if (s[i] == '$')
//             break;
//         i++;
//     }
//     str = f_substr(s, 0 ,i);
//     return str;
// }
// char *type_one(char *s, t_env *env)
// {
//     t_expand e;
//     char *str;
//     char *r = NULL;
//     int i = 0;

//     e.end = ft_strlen(s);
//     e.start = 0;
//     e.is_expand = true;
//     if (s[0] == '\'' || s[0] == '\"')
//     {
//         e.start++;
//         if (s[0] == '\'')
//             e.is_expand = false;
//         e.end--;
//     }
//     if ((e.end - e.start) == 0)
//         return (f_strdup(""));
//     str = f_substr(s, e.start, e.end - 1);
//     while (str[i])
//     {
//         if (str[i] == '$')
//         {
//             e.key = getkey(str + i);
//             i += ft_strlen(e.key) - 1;
//             e.value = ft_bring_key(e.key , env, e.is_expand);
//            r = f_strjoin(r,e.value);
//         }
//         else
//         {
//             e.start_letter = i;
//             while (str[i] && str[i] != '$')
//                 i++;
//             // if (str[i] == '$')
//             //     i--;
            
//             r = f_strjoin(r, f_substr(str, e.start_letter, i--));
//             printf("str2[%s]\n",r);
//         }
//         i++;
//     }
//     printf("str[%s]\n",str);
//     return (r);
// }

// char * ft_expand_value(char *s, t_env *envi)
// {
//     size_t i;
//     t_expand e;
//     char *r = NULL;
//     i = 0;
//     while (s[i])
//     {
//         if (s[i] == '\'' || s[i] == '\"')
//         {
//             printf("her1\n");
//             r = f_strjoin(r, type_one(f_substr(s, i, skip_betw_quotes3(s, &i)), envi));
//             printf("r[%s]\n",r);
//             printf("her1\n");
//             i--;
//         }
//         else if (s[i] == '$')
//         {
//            e.key = getkey(s + i);
//             i += ft_strlen(e.key) - 1;
//            e.value = ft_bring_key(e.key,envi,true);
//            r = f_strjoin(r,e.value);
//         }
//         else
//         {
//             e.start = i;
//             while (s[i] && s[i] != '$' && s[i] != '\'' && s[i] != '\"')
//                 i++;
//             r = f_strjoin(r, f_substr(s, e.start, i--));
//         }
//         i++;
//     }
//     return (r);
// }


//------------------------younes-----------------------------------
// void    expand_input(char *str, t_env *envs)
// {
//     int i;
//     char *new;
//     int start;
//     char *tmp = NULL;
//     char *value;

//     value = NULL;
//     new = NULL;
//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == '\'')
//         {
//             // new = ft_strjoin(new, "'");
//             start = i;
//             i++;
//             while (str[i] != '\'' && str[i])
//                 i++;
//             tmp = f_substr(str, start, i - start);
//             new = f_strjoin(new, tmp);
//             if (str[i] == '\'')
//             {
//                 new = ft_strjoin(new, "'");
//                 i++;
//             }
//         }
//         else
//         {
//             if (str[i] == '"')
//             {
//                 new = f_strjoin(new, "\"");
//                 i++;
//             }
//             while (str[i] && str[i] != '"')
//             {
//                 start = i;
//                 while (str[i] && str[i] != '$' && str[i] != '"')
//                     i++;
//                 if (start != i)
//                 {
//                     tmp = f_substr(str, start, i - start);
//                     new = ft_strjoin(new, tmp);
//                 }
//                 if (str[i] == '$')
//                 {
//                     start = 1;
//                     i++;
//                     while (str[i] && str[i] == '$' && str[i] != '"')
//                     {
//                         start++;
//                         i++;
//                     }
//                     if (start % 2 == 0)
//                     {
//                         start = start / 2;
//                         while (start)
//                         {
//                             new = ft_strjoin(new, "$");
//                             start--;
//                         }
//                     }
//                     else
//                     {
//                         start = start / 2;
//                         while (start > 1)
//                         {
//                             new = ft_strjoin(new, "$");
//                             start--;
//                         }
//                         if (ft_isdigit(str[i]))
//                             i++;
//                         else
//                         {
//                             if (!ft_isalnum(str[i]))
//                                 new = ft_strjoin(new, "$");
//                             start = i;
//                             while (str[i] && ft_isalnum(str[i]) && str[i] != '"')
//                                 i++;
//                             if (start != i)
//                             {
//                                 tmp = NULL;
//                                 // tmp = f_strjoin(tmp, "$");
//                                 tmp = f_substr(str, start-1, i - start+1);
//                                 value = ft_bring_key(tmp, envs, true);
//                                 if (value)
//                                     new = ft_strjoin(new, value);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     new = ft_strjoin(new, "\0");
//     printf("res: |%s|\n", new);
    
// }

// //------------------------amin----------------------------
// void ft_expanding(char *str, char **env)
// {
//     char **array;
//     char **result;
//     char **retun;
//     t_env *envi;

//     result = NULL;
//     envi = env_set(env);
//     array = f_split(str, ' ');
//     int len = ft_counter(str, ' ');
//     result = (char **)f_calloc(sizeof(char *), len + 1);
//     int i = 0;
    
//     while (array[i])
//     {
//         printf("first parsing ;%s;\n", array[i]);
//         i++;
//     }
//     int j = 0;
//     i = 0;
//     while (array[i])
//     {
//         if (ft_strcmp(array[i], "<<") == 0)
//         {
//             result[j++] = ft_strdup(array[i++]);
//             result[j++] = ft_strdup(array[i]);
//         }
//         else
//             result[j++] = ft_expand_value(array[i], envi);
//         i++;
//     }
//     i = 0;
//     while (result[i])
//     {
//         printf("expand{%s}\n",result[i++]);
//     }
    
    // printf("result = %s\n",f_expanding_quotes(result));
//}

//------------------------------------------------------------------------//
/*
 if (ft_check_exist_charracter(array[i]) == 1)
        {
            result = f_strjoin(result, ft_expend_just_dollar(array[i], envi));
        }
        else if (ft_check_exist_charracter(array[i]) == 2)
            result = f_strjoin(result, array[i]);
        else if (ft_check_exist_charracter(array[i]) == 3)
            result = f_strjoin(result, ft_expend_just_dollar(array[i], envi));
        else
            result = f_strjoin(result, array[i]);
        i++;
*/
// void    ft_expanding(char *s,char **env)
// {
//     t_expand e;
//     int i;
//     char *r;

//     e.end = ft_strlen(s);
//     e.start = 0;
//     e.is_expand = true;
//     if (s[0] == '\'' || s[0] == '\"')
//     {
//         e.start++;
//         if (s[0] == '\'')
//             e.is_expand = false;
//         e.end--;
//     }

// }
/*
char *s = =
char *value;
char *r = NULL;
int i = 0;
while(s[i])
{
    if (s[i] == '$')
    {
        value = get_key(s + i);
        i + =ft_strlen(value);
        r = join(r , expnd(value));
    }else
    {
        start = i;
        while(s[i] && s[i] != '$')
            i++;
        if (s[i] == '$')
            i--;
        value = ft_rang(s, start, i);
        r = join(r ,value);
    }
    i++;
}
*/

