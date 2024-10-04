/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/04 03:57:43 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int pipe_check(char *s)
{
    int i = 0;
    int k = 0;
    if(!s)
        return(0);
    while(s[i])
    {
        if(s[i] == '|')
            k++;
        i++;
    }
    return(k);
}
int pars(t_top **cmd,char *input)
{
	int i = -1;
	char **comond;
	(*cmd)->cmd = aloc_comond((*cmd)->env->env,NULL);
	if(!(*cmd)->cmd)
		return -1;
	(*cmd)->head = (*cmd)->cmd;
	(*cmd)->n_pipe = pipe_check(input);
	if((*cmd)->n_pipe > 0)
	{
		comond = init_mult_cmd((*cmd)->a,(*cmd)->n_pipe);
        i = -1;
		while(comond[++i])
		{
			if(handel_comond(comond[i],&(*cmd)->cmd,(*cmd)->env->env))
            {
			    (*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],(*cmd)->env->env);
            }
            if(comond[i + 1] != NULL)
			    (*cmd)->cmd->next = aloc_comond((*cmd)->env->env,(*cmd)->head);
            else
            {
                (*cmd)->cmd->next = NULL;
                break;
            }
            
			if(!(*cmd)->cmd->next)
				exit(150);
			(*cmd)->cmd = (*cmd)->cmd->next;
		}
		(*cmd)->cmd = (*cmd)->head;
		return(2);
	}
    else
    {
        comond = ft_joinlist((*cmd)->a);
		if(!handel_onecomond(comond,&(*cmd)->cmd,(*cmd)->env->env))
            return(-1);
		(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],(*cmd)->env->env); 
        return(1);
    }
}
bool    handel_onecomond(char **words,t_exec_cmd **comond,char **env)
{
    char **args;  
    args = master(sizeof(char *) * (count_words(words) + 1),1);
    char *temp;
    int i = 0;
    int j = 0;

    while(words[i] != NULL)
    {
        if(words[i][0] == '$')
        {
            if(i > 0 && pasabel(words[i-1] ))
            {
                temp = words[i];
                words[i] =  expand(words[i],env);
                // free(temp);
            }
        }
        if(ft_strcmp(words[i],"<<") == 0)
        {
            (*comond)->infd =  ft_herdoc(words[++i],env);
            if((*comond)->infd == -1)
                return (perror(words[i]) ,false);
        }
        else if( ft_strcmp(words[i],">") == 0)
        {
            (*comond)->outfd = out_redirect(words[++i]);
            if((*comond)->outfd == -1)
                return (perror(words[i]) ,false);
        }
        else if(ft_strcmp(words[i],"<") == 0)
        {
            if(words[i + 1] != NULL)
            {
                (*comond)->infd = in_redirect(words[++i]);
                if((*comond)->infd == -1)
                    return (perror(words[i]) ,false);
            }
            else
                return false;
        }
        else if(ft_strcmp(words[i],">>") == 0)
        {
            (*comond)->outfd = append(words[++i]);
            if((*comond)->outfd == -1)
                return (perror(words[i]) ,false);
        }
        else
        {
            if(((i >= 1 && pasabel(words[i - 1]) == true) || i == 0 ))
            {
                args[j] = words[i];
                j++;
            }
            i++;
        }
    }
    if(!args)
        return(false);
    args[j] = NULL;
    (*comond)->args = args;
    (*comond)->cmd = words[0];
    return(args);
}