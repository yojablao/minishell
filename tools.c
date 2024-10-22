/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:50:24 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/22 16:44:09 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




char	*f_substr(char const *s, unsigned int start, size_t len)
{
	char		*new;
	char		*src;
	size_t		l;
	size_t		i;

	if (!s)
		return (NULL);
	src = (char *)s;
	l = ft_strlen(s);
	i = 0;
	if (start >= l)
		return (f_strdup(""));
	if (len > l - start)
		len = (l - start);
	new = (char *)master((len + 1) * sizeof(char),1);
	if (!new)
		return (NULL);
	while (i < len)
		new[i++] = src[start++];
	new[i] = '\0';
	return (new);
}

t_env     *env_set(char **envi)
{
    t_env    *env = NULL;
    t_env    *new_env = NULL;
    t_env    *tmp = NULL;
    
    int i = 0;
    int j;
    if(!envi)
        return NULL;
    while(envi[i])
    {
        j = 0;
        // printf("-  - %s -   -\n", envi[i]);
        while(envi[i][j])
        {
            if(envi[i][j] == '=')
            {
                new_env = master(sizeof(t_env),1);
                if(!new_env)
                    return NULL;
                envi[i][j] = '\0';
                new_env->key = f_strdup(&envi[i][0]);
                new_env->value= f_strdup(&envi[i][j + 1]);
                new_env->valid = 1;
                new_env->next = NULL;
                if(tmp == NULL)
                    env = new_env;
                else
                    tmp->next = new_env;
                tmp = new_env;
                envi[i][j] = '=';

                break;

            }
            j++;
        }
        i++;
    }
    return (env);
}
int count_words(char **words)
{
    int count = 0;

    while (words[count] != NULL)
    {
        count++;
    }

    return count;  
}
bool    pasabel(char *c)
{
    if(ft_strcmp(c,"<") == 0)
        return (false);
    if(ft_strcmp(c,"<<") == 0)
        return(false);
    if(ft_strcmp(c,">") == 0)
        return (false);
    if(ft_strcmp(c,"|") == 0)
        return (false);
    
    return(true);
}
void ft_printf_a(t_list *a)
{
    t_list *tmp = a;
    while(tmp)
    {
        printf("{%s}\n",tmp->content);
        tmp = tmp -> next;
    }
}
char **ft_joinlist(t_list *a,t_environment **env)
{
    if (!a) return NULL; 
    int s = -1;
    int p = ft_lstsize(a);
    char **words = master(sizeof(char *) * (p + 1), 1); 
    if (!words) return NULL; 
    int i = 0;
    while (a)
    {
        if (s == -1 || s != 4)
            words[i] = ft_expand1(a->content,(*env)->env);
        else
            words[i] = f_strdup(a->content);
        s = a->stat;
        a = a->next;        
        i++;
    }
    words[i] = NULL; 
    return words; 
}
// bool    handel_comond(char *cmd,t_exec_cmd **comond,char **env)
// {
//      char **words = f_split(cmd,' ');
//     char **args;  
//     args = master(sizeof(char *) * (count_words(words) + 1),1);
//     int i = 0;
//     int j = 0;

//     while(words[i] != NULL)
//     {
//         if(ft_strcmp(words[i],"<<") == 0)
//         {

//             (*comond)->infd =  ft_herdoc(words[++i],env);
//             if((*comond)->infd == -1)
//                 return (perror(words[i]) ,false);
//         }
//         else if( ft_strcmp(words[i],">") == 0)
//         {
//             (*comond)->outfd = out_redirect(words[++i]);
//             if((*comond)->outfd == -1)
//                 return (perror(words[i]) ,false);
//         }
//         else if(ft_strcmp(words[i],"<") == 0)
//         {
//             (*comond)->infd = in_redirect(words[++i]);
//             if((*comond)->infd == -1)
//                 return (perror(words[i]) ,false);
//         }
//         else if(ft_strcmp(words[i],">>") == 0)
//         {
//             (*comond)->outfd = append(words[++i]);
//             if((*comond)->outfd == -1)
//                 return (perror(words[i]) ,false);
//         }
//         else
//         {
//             if(((i >= 1 && pasabel(words[i - 1]) == true) || i == 0 ))
//             {
//                 args[j] = words[i];
//                 j++;

//             }

//             i++;
//         }
//     }
//     if(!args)
//         return(false);
//     args[j] = NULL;
//     (*comond)->args = args;
//     (*comond)->cmd = args[0];
//     return(args);
// }
void filehandler(t_exec_cmd **s)
{
        // printf("%d\n",(*s)->infd);
        // printf("%d\n",(*s)->outfd);
    if ((*s)->infd != 0)
    { 
        if (dup2((*s)->infd, 0) == -1)
            exit(EXIT_FAILURE);
        close((*s)->infd); 
    }
    if ((*s)->outfd != 1) {  
        if (dup2((*s)->outfd, 1) == -1) {
            perror("dup2 output redirection failed");
            exit(EXIT_FAILURE);
        }
        close((*s)->outfd);  
    }
}
void f(void *content)
{
    char *s = (char *)content;  // Cast content to char as it's passed as void *
    int i = 0;
    int j = 0;
    int single_q = 0;
    int double_q = 0;

    while (s[i])
    {
        if (s[i] == '\'' && !double_q)
            single_q = !single_q;
        else if (s[i] == '"' && !single_q)
            double_q = !double_q;
        else
            s[j++] = s[i];  // Copy valid characters to the current position
        i++;
    }
    s[j] = '\0';  // Null-terminate at position j
}
