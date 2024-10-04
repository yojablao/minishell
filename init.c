/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:53:57 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/04 03:56:58 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_top *init(char **envi)
{
	t_top *data;

	data = malloc(sizeof(t_top));
	if(!data)
		return(NULL);
	data->env = malloc(sizeof(t_environment));
	data->env->env = envi;
	data->cmd = NULL;
	data->env->lenv = env_set(envi);
	return(data);
}
char **init_mult_cmd(t_list *a, int p)
{
    char *tmp;
    char *line_parsed = NULL;
	char **comond;
    comond = master(sizeof(char **) * (p + 2),1);
    while(a)
    {
        if(a->content[0] != '|' || a->next != NULL)
        {
            if (!line_parsed) 
                line_parsed = f_strdup(a->content); 
            else
            {
                tmp = line_parsed;
                line_parsed =f_strjoin(line_parsed ,a->content);
                
            }
            tmp = line_parsed;
            line_parsed = f_strjoin(line_parsed ," ");
        }
        a = a->next;
    }
    if (line_parsed)
        comond = f_split(line_parsed,'|');
    return (comond);
}
t_exec_cmd	*aloc_comond(char **env ,t_exec_cmd *s)
{
	t_exec_cmd *st;
    st = master(sizeof(t_exec_cmd),1);
    if (!(st)) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
	st->head = s;
    st->infd = 0;
    st->outfd = 1;
    st->next = NULL;
    st->cmd = NULL;
    st->args = NULL;
    st->env = env;
	return(st);
}