/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/19 18:56:26 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int pipe_check(t_list *a)
{
    int i = 0;
    while(a)
    {
        if(ft_strcmp(a->content,"|") == 0)
            i++;
        a = a->next;
    }
    return(i);
}


int pars(t_shell **cmd,char *input)
{
    if (!syntax(input,cmd))
		return (printf("syntax error\n"), -1);
        ft_printf_a((*cmd)->a);
	(*cmd)->cmd = aloc_comond((*cmd)->cmd);
	if(!(*cmd)->cmd || !(*cmd)->a)
		return -1;
	(*cmd)->head = (*cmd)->cmd;
	(*cmd)->n_pipe = pipe_check((*cmd)->a);
	if((*cmd)->n_pipe > 0)
	{
        // printf("jkruhgnv\n");
        init_pipe_line(cmd);
		(*cmd)->cmd = (*cmd)->head;
		return(2);
	}
    else
    {
        if(comond_init(cmd) == false)
            return(-1);
        return(1);
    }
}

bool    handel_comond(char **words,t_exec_cmd **comond,t_environment **env)
{
    char **args;  
    int i = 0;
    int j = 0;


    args = master(sizeof(char *) * (count_words(words) + 1),1);
    if(!args)
        return(false);
    while(words[i] != NULL)
    {
        if(!handel_redirect(&i,words,comond,(*env)->env))
            return (false);
        else if(words[i])
        {
            if(((i >= 1 && pasabel(words[i - 1]) == true) || i == 0 ))
            {
                args[j] = words[i];
                j++;
            }
            i++;
        }
        // printf("-- %s --\n", words[i]);
    }
    args [j]= NULL;
    (*comond)->args = args;
    return(true);
}
static char *find_pexec(char *comond,char *value)
{
    char    *path;
    char    **fullpath;
    int i;

    i = -1;
    fullpath = f_split(value, ':');
    while(fullpath[++i] != NULL)
    {
        fullpath[i] =  f_strjoin(fullpath[i],"/");
        if(!fullpath[i])
            return NULL;
        path = f_strjoin(fullpath[i],comond);
        if(!path[i])
            return NULL;
        if(!access(path, X_OK))
            return(path);
    }
    return(NULL);
}
char    *find_comond(char *comond,t_env **env)
{
    t_env    *tmp ;

    if(!comond)
        return NULL;
    tmp = (*env);
    if(ft_strchr(comond,'/'))
        return(comond);
    while(tmp !=   NULL && (ft_strcmp(tmp->key,"PATH")) != 0)
    {
        if((ft_strcmp(tmp->key,"PATH")) == 0)
            break;
        if(tmp->next == NULL)
            break;
        else
            tmp = tmp->next;
    }
    if((ft_strcmp(tmp->key, "PATH")) == 0)
        return(find_pexec(comond,tmp->value));
    return (NULL);
}
size_t	f_strlen2d(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
