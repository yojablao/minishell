/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:50:24 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/23 23:22:14 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 #include <errno.h>
#include <string.h>

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
void add_env(t_env **head, char *key, char *value)
{
    t_env    *new_env;
    t_env    *tmp;

    new_env = master(sizeof(t_env), 1);
    new_env->key = f_strdup(key);
    new_env->value = f_strdup(value);
    new_env->valid = 1;
    new_env->next = NULL;

    if (*head == NULL)
        *head = new_env;
    else
    {
        tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new_env;
    }
}
t_env     *env_set(char **envi)
{
	t_env    *env = NULL;
	
	int i = 0;
	int j;
	if(!envi)
		return NULL;
	while(envi[i])
	{
		j = 0;
		while(envi[i][j])
		{
			if(envi[i][j] == '=')
			{
				envi[i][j] = '\0';
				add_env(&env,&envi[i][0],&envi[i][j + 1]);
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
		count++;
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
	char *tmp;
	int p = ft_lstsize(a);
	char **words = master(sizeof(char *) * (p + 1), 1); 
	if (!words) return NULL; 
	int i = 0;
	while (a)
	{
		tmp = ft_expand1(a->content,(*env)->env);
		if (tmp && *tmp)
		{
			if (s == -1 || s != 4)
				words[i] = tmp;
			else
				words[i] = f_strdup(a->content);
			i++;     
		}
		s = a->stat;
		a = a->next;        
	}
	words[i] = NULL; 
	return words; 
}
void filehandler(t_exec_cmd **s)
{
	if ((*s)->infd != 0)
	{ 
		printf("%d\n", (*s)->infd);
		if (dup2((*s)->infd, STDIN_FILENO) == -1)
		{
			perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
		close((*s)->infd); 
			// sleep(20);
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
	char *s;
	int i = 0;
	int j = 0;
	int single_q;
	int double_q;

	single_q = 0;
	double_q = 0;
	s = (char *)content;
	while (s[i])
	{
		if (s[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (s[i] == '"' && !single_q)
			double_q = !double_q;
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}
