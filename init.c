/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:53:57 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/19 18:06:20 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **creat_env(void)
{
    char **env;
    char buffer[1024];
    env = master(sizeof(char *) * 5,1);
    env[0] = f_strdup("OLDPWD");
    env[1] = f_strdup(f_strjoin("PWD=",getcwd(buffer,sizeof(buffer))));
    env[2] = f_strdup("SHLVL=1");
    env[3] = NULL;
    return (env);
}
void update_shell_lvl(t_env **env)
{
    char *value;
    int i;
    value = extract_value((*env),"SHLVL");
    i = ft_atoi(value);
    value = ft_itoa(i + 1);
    add_to_env(env,"SHLVL",value,0);
    free(value);
}

t_environment *env_setup(char **envi)
{
    t_environment *env;
	env = malloc(sizeof(t_environment));
     if(!env)
        return NULL;
    if(!*envi)
    {
        env->env = creat_env();
	    env->lenv = env_set(env->env);

    }
    else
    {
	    env->lenv = env_set(envi);
        update_shell_lvl(&env->lenv);
    }
    if(!env->lenv)
        return NULL;
	env->env = join_to_env(env->lenv);
    return(env);
}
t_shell *init(char **envi)
{
	t_shell *data;

	data = malloc(sizeof(t_shell));
	if(!data)
		return(NULL);
      
    data->env = env_setup(envi);
    if(!data->env)
        return(free(data),NULL);
	data->cmd = NULL;
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
t_exec_cmd	*aloc_comond(t_exec_cmd *s)
{
	t_exec_cmd *st;
    st = master(sizeof(t_exec_cmd),1);
    if (!(st)) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    if(!s)
	    s = st->head;
    else
	    st->head = s;
    st->infd = 0;
    st->outfd = 1;
    st->next = NULL;
    st->cmd = NULL;
    st->args = NULL;
    st->builting = false;
	return(st);
}
bool handel_redirect(int *j,char **words ,t_exec_cmd **comond,char **env)
{
    if(ft_strcmp(words[(*j)],"<<") == 0)
    {
        (*comond)->infd =  ft_herdoc(words[++(*j)],env);
        if((*comond)->infd == -1)
            return (perror(words[(*j)]) ,false);
    }
    else if( ft_strcmp(words[(*j)],">") == 0)
    {
        (*comond)->outfd = out_redirect(words[++(*j)]);
        if((*comond)->outfd == -1)
            return (perror(words[(*j)]) ,false);
    }
    else if(ft_strcmp(words[(*j)],"<") == 0)
    {
            (*comond)->infd = in_redirect(words[++(*j)]);
            if((*comond)->infd == -1)
                return (perror(words[(*j)]) ,false);
    }
    else if(ft_strcmp(words[(*j)],">>") == 0)
    {
        (*comond)->outfd = append(words[++(*j)]);
        if((*comond)->outfd == -1)
            return (perror(words[(*j)]) ,false);
    }
    return (true);
}
bool comond_init(t_shell **cmd)
{
	char **comond;

    comond = ft_joinlist((*cmd)->a,&(*cmd)->env);
    // str = ft_expand(comond[i],(*cmd)->env->lenv);
    // comond = expand_f(comond,(*cmd)->env->lenv);
	if (!handel_comond(comond,&(*cmd)->cmd,&(*cmd)->env))
        return (get_exit(1,0),false);
    if(check_internal_builtins(&(*cmd)->cmd,&(*cmd)->env) == 1)
        return false;
	(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],&(*cmd)->env->lenv);
    if(!(*cmd)->cmd->cmd)
    {
        ft_putstr_fd("minishell:  ",2);

        ft_putstr_fd((*cmd)->cmd->args[0],2);
        ft_putstr_fd(": command not found\n",2);
        get_exit(127,0);
        return(false);
    }
    else
        add_to_env(&(*cmd)->env->lenv,"_",(*cmd)->cmd->cmd,0);
    return (true);
}
bool init_pipe_line(t_shell **cmd)
{
    char ** comond;
    int i = 0;
    comond = init_mult_cmd((*cmd)->a,(*cmd)->n_pipe);
    i = -1;
    char *str;
    // comond = expand_f(comond,(*cmd)->env->lenv);
    // expand_part(cmd);
	while(comond[++i])
	{
        str = ft_expand(comond[i],(*cmd)->env->lenv);
		if(handel_comond(f_split(str,' '),&(*cmd)->cmd,&(*cmd)->env))
        {
		    (*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],&(*cmd)->env->lenv);
            if((*cmd)->cmd->cmd)
                add_to_env(&(*cmd)->env->lenv,"_",(*cmd)->cmd->cmd ,0);
        }
        if(comond[i + 1] != NULL)
		    (*cmd)->cmd->next = aloc_comond((*cmd)->head);
        else
        {
            (*cmd)->cmd->next = NULL;
            break;
        }
		if(!(*cmd)->cmd->next)
			return false;
	    (*cmd)->cmd = (*cmd)->cmd->next;
	}
	return true;
}
