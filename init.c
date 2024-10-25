/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:53:57 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/25 03:43:40 by yojablao         ###   ########.fr       */
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

    value = extract_value((*env),"SHLVL");
    if(!value || !*value || ft_atoi(value) > 999)
        return (add_to_env(env,"SHLVL","1",0));
    if (ft_atoi(value) == 2147483647)
        return (add_to_env(env,"SHLVL","0",0));
    if (ft_atoi(value) < 0)
        return (add_to_env(env,"SHLVL","0",0));
    if(ft_atoi(value) == 999)
        return (add_to_env(env,"SHLVL","",0));
    value = ft_itoa(ft_atoi(value) + 1);
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
        add_key_env(&env->lenv,"PATH",defaultpath);
        env->env = join_to_env(env->lenv);
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
        comond = f_split(line_parsed,'|','|');
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

int typecheck(char *word,t_exec_cmd **comond)
{
    if(ft_strcmp(word,"<<") == 0)
    {
        if((*comond)->infd != 0)
            close((*comond)->infd);
        return(1);
    }
    else if(ft_strcmp(word,"<") == 0)
    {
        if((*comond)->infd != 0)
            close((*comond)->infd);    
        return(2);
    }
    else if(ft_strcmp(word,">>") == 0)
    {
        if((*comond)->outfd != 1)
            close((*comond)->outfd);
        return(3);
    }
    else if(ft_strcmp(word,">") == 0)
    {   
        if((*comond)->outfd != 1)
            close((*comond)->outfd);
        return(4);
    }
    return(0);
}
static bool	handle_infd(int type, int *j, char **words, t_exec_cmd **cmd, t_environment **env)
{
	if (type == 1)
		(*cmd)->infd = ft_herdoc(words[++(*j)], env);
	else
		(*cmd)->infd = in_redirect(words[++(*j)]);
	if ((*cmd)->infd == -1)
	{
		perror(words[(*j)]);
		return (false);
	}
	return (true);
}

static bool	handle_outfd(int type, int *j, char **words, t_exec_cmd **cmd)
{
	if (type == 3)
		(*cmd)->outfd = out_redirect(words[++(*j)]);
	else
		(*cmd)->outfd = append(words[++(*j)]);
	if ((*cmd)->outfd == -1)
	{
		perror(words[(*j)]);
		return (false);
	}
	return (true);
}

bool	handel_redirect(int *j, char **words, t_exec_cmd **cmd, t_environment **env)
{
	int	type;

	type = typecheck(words[*j], cmd);
	if (type == 1 || type == 2)
		return (handle_infd(type, j, words, cmd, env));
	else if (type == 3 || type == 4)
		return (handle_outfd(type, j, words, cmd));
	return (true);
}
void comnond_err(char *s)
{
    ft_putstr_fd("minishell:  ",2);
    ft_putstr_fd(s,2);
    ft_putstr_fd(": command not found\n",2);
}
bool comond_init(t_shell **cmd)
{
	char **comond;
    // int i = -1;

    comond = ft_joinlist(&(*cmd)->a,&(*cmd)->env);
    // while(comond[++i])
    //     printf("---%s--\n",comond[i]);
    if(!comond[0])
        return(false);

	if (!handel_comond(comond,&(*cmd)->cmd,&(*cmd)->env))
        return (get_exit(1,0),false);
    if(!(*cmd)->cmd->args[0])
        return (close_open_fd(&(*cmd)->cmd),false);
    if(check_internal_builtins(&(*cmd)->cmd,&(*cmd)->env) == 1)
        return false;
	(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],&(*cmd)->env->lenv);
    if(!(*cmd)->cmd->cmd)
    {
        comnond_err((*cmd)->cmd->args[0]);
        get_exit(127,0);
        return(false);
    }
    else
        add_to_env(&(*cmd)->env->lenv,"_",(*cmd)->cmd->cmd,0);
    return (true);
}
// char **init_mult_cmd(t_list *a, t_environment **env)
// {
//     char **comond;
    
//     if (!a)
//         return NULL;

//     comond = ft_joinlist(a, env);
    
//     if (comond && comond[0] != NULL)
//         comond = f_split(comond[0], '|', '|');
    
//     return comond;
// }
// bool init_pipe_line(t_shell **cmd)
// {
//     char **comond;
//     int i = 0;

//     // Use ft_joinlist to join command strings and expand environment variables
//    
    
//     if (!comond || !comond[0])  // Check if there are no commands
//         return false;
//     i = -1;
//     while (comond[++i])
//     {
//         // Split the expanded command by spaces and tabs into arguments
//         if (handel_comond(f_split(comond[i], ' ', '\t'), &(*cmd)->cmd, &(*cmd)->env))
//         {
//             // Find the command in the PATH
//             (*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0], &(*cmd)->env->lenv);
//             if ((*cmd)->cmd->cmd)  // If the command exists
//             {
//                 // Update the environment with the last executed command
//                 add_to_env(&(*cmd)->env->lenv, "_", (*cmd)->cmd->cmd, 0);
//             }
//             else  // If command is not found, print an error
//             {
//                 comnond_err((*cmd)->cmd->args[0]);
//                 get_exit(127, 0);
//                 return false;
//             }
//         }
//         else
//         {
//             return false;  // Command handling failed, return false
//         }

//         // If there is another command in the pipeline, allocate space for it
//         if (comond[i + 1] != NULL)
//         {
//             (*cmd)->cmd->next = aloc_comond((*cmd)->head);
//         }
//         else
//         {
//             (*cmd)->cmd->next = NULL;  // No more commands, break out of the loop
//             break;
//         }

//         // Move to the next command in the pipeline
//         if (!(*cmd)->cmd->next)
//             return false;  // Memory allocation failed
//         (*cmd)->cmd = (*cmd)->cmd->next;
//     }

//     return true;
// }
bool init_pipe_line(t_shell **cmd)
{
    char ** comond;
    int j = 0;

	while((*cmd)->n_pipe >= j)
	{
        comond = ft_joinlist(&(*cmd)->a, &(*cmd)->env);
		if(handel_comond(comond,&(*cmd)->cmd,&(*cmd)->env))
        {
		    (*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],&(*cmd)->env->lenv);
            if((*cmd)->cmd->cmd)
                add_to_env(&(*cmd)->env->lenv,"_",(*cmd)->cmd->cmd ,0);
        }
        else
            return false;
        if((*cmd)->n_pipe >= j + 1)
		    (*cmd)->cmd->next = aloc_comond((*cmd)->head);
        else
        {
            (*cmd)->cmd->next = NULL;
            break;
        }
		if(!(*cmd)->cmd->next)
			return false;
	    (*cmd)->cmd = (*cmd)->cmd->next;
        j++;
	}
	return true;
}
