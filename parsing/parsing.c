/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/30 04:35:32 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int pipe_check(t_list *a)
{
    int i;

    i = 0;
    while (a)
    {
        if (a->stat == 0)
            i++;
        a = a->next;
    }
    return (i);
}

int parsing_input(t_shell **cmd, char *input)
{
    if (!syntax(input, cmd))
        return (get_exit(258, 0), printf("syntax error\n"), -1);
    (*cmd)->cmd = aloc_comond((*cmd)->cmd);
    (*cmd)->head =(*cmd)->cmd;
    if (!(*cmd)->cmd || !(*cmd)->a)
        return -1;
    (*cmd)->head = (*cmd)->cmd;
    (*cmd)->n_pipe = pipe_check((*cmd)->a);
    if((*cmd)->n_pipe > 1390)
        return(ft_putstr_fd("bash: fork: Resource temporarily unavailable\n",2),-1);
    
    if ((*cmd)->n_pipe > 0)
    {
        if (init_pipe_line(cmd) == false)
            return (-1);
        (*cmd)->cmd = (*cmd)->head;
        return (2);
    }
    else
    {
        if (comond_init(cmd) == false)
            return (-1);
        return (1);
    }
}

bool handel_comond(char **words, t_exec_cmd **comond, t_environment **env)
{
    char **args;
    int i;
    int j;

    i = 0;
    j = 0;
    args = master(sizeof(char *) * (count_words(words) + 1), 1);
    if (!args)
        return true;
    while (words[i] != NULL)
    {
        if(!handel_redirect(&i, words, comond, env))
            return (false);
        else if (words[i] != NULL)
        {
            if (i == 0 || (i >= 1 && pasabel(words[i - 1]) == true))
                args[j++] = words[i];
            i++;
        }
    }
    args[j] = NULL;
    (*comond)->args = args;
    return true;
}

static char *find_pexec(char *comond, char *value)
{
    char *path;
    char **fullpath;
    int i;

    

    i = -1;
    fullpath = f_split(value, ':', ':');
    while (fullpath[++i] != NULL)
    {
        fullpath[i] = f_strjoin(fullpath[i], "/");
        if (!fullpath[i])
            return NULL;
        path = f_strjoin(fullpath[i], comond);
        if (!path[i])
            return NULL;
        if (!access(path, F_OK))
            return (path);
    }
    return (NULL);
}
char *find_comond(char *comond, t_env **env)
{

    // if (comond[0] == '.' && comond[1])
    //     return (comond);
    if(comond[0] == '.' && !comond[1])
    {
        ft_putstr_fd("minshell: .: filename argument required\n",2);
        ft_putstr_fd(".: usage: . filename [arguments]\n",2);
        get_exit(2,0);
        return(NULL);
    }
    if (ft_strchr(comond, '/'))
    {
        if (comond[ft_strlen(comond) - 1] == '/')
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(comond, 2);
            ft_putstr_fd(": is a directory\n", 2);
            get_exit(126, 0);
            return NULL;
        }
        else
        {
            // ft_putstr_fd("minishell: ", 2);
            // ft_putstr_fd(comond, 2);
            if (access(comond, X_OK))
                ft_putstr_fd(": No such file or directory\n", 2);
            // get_exit(127, 0);
            return comond;
        }
    }
    char *path;
    path = extract_value((*env),"PATH");
    if(path)
    { 
        char *tmp1 = find_pexec(comond, path);
        if(tmp1 == NULL)
        {
                comnond_err(comond,*env);
                get_exit(127, 0);   
                return(NULL);
        }
        else
            return(tmp1);
    }
    else
        return(comond);
    return(NULL);
    // while (tmp != NULL && (ft_strcmp(tmp->key, "PATH")) != 0)
    // {
    //     if ((ft_strcmp(tmp->key, "PATH")) == 0)
    //         break;
    //     if (tmp->next == NULL)
    //         break;
    //     else
    //         tmp = tmp->next;
    // }
    // if ((ft_strcmp(tmp->key, "PATH")) == 0)
    // {
    // }
}
size_t f_strlen2d(char **str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}
