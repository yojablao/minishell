/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/19 18:40:21 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int check_internal_builtins(t_exec_cmd **s,t_environment **env)
{
    (void)env;
    (void)s;
    
    if(ft_strcmp((*s)->args[0],"unset") == 0)
        return( un_set_builting(s,env),add_to_env(&(*env)->lenv,"_",(*s)->args[0],0),1);
    if(ft_strcmp((*s)->args[0],"cd") == 0)
        return( cd_builting(s,env),add_to_env(&(*env)->lenv,"_",(*s)->args[0],0),1);
    if(ft_strcmp((*s)->args[0],"export") == 0)
        return(export_builtin((*s)->args,env),add_to_env(&(*env)->lenv,"_",(*s)->args[0],0),1);
    if(ft_strcmp((*s)->args[0],"env") == 0)
        return( env_build((*env)->lenv),add_to_env(&(*env)->lenv,"_",(*s)->args[0],0),1);
    if(ft_strcmp((*s)->args[0],"pwd") == 0 || ft_strcmp((*s)->args[0],"PWD") == 0)
        return( pwd_builting((*env)->lenv),add_to_env(&(*env)->lenv,"_",(*s)->args[0],0),1);
    return(0);
}
void fail_case(char *fail)
{
    perror(fail);
    exit(EXIT_FAILURE);   
}
int     exic(t_exec_cmd **s,t_shell **data)
{
    int     status;
    pid_t pid;

    pid  = fork();
    if(pid == -1)
        return(1);
    if(pid == 0)
    {
        if(child(s,(*data)) == EXIT_FAILURE)
            return(1);
    }
    else 
        waitpid(pid,&status,0);
    return(0);
}
void exic_path(int *prev,int *root,t_exec_cmd **s,t_shell **data)
{
    
    t_exec_cmd *cmd = (*s);
    if (prev[0] != -1)
    {
        if (dup2(prev[0], STDIN_FILENO) == -1)
            fail_case("dup2 input redirection failed");
        close(prev[0]);
    }
    if (cmd->next != NULL)
    {

        if (dup2(root[1], STDOUT_FILENO) == -1)
            fail_case("dup2 output redirection failed");
    }
    if (prev[1] != -1)
        close(prev[1]);
    close(root[0]);
    close(root[1]);
    child(&cmd, *data);
    exit(EXIT_FAILURE); 
}
void parent_part(pid_t pid,int *root,int *prev,t_exec_cmd **s)
{
    t_exec_cmd *cmd = (*s);
    waitpid(pid, 0, 0);
    if (cmd->next != NULL)
        close(root[1]);
    if (prev[0] != -1)
        close(prev[0]);
    prev[0] = root[0];
    prev[1] = root[1];

        
}
void close_files(t_exec_cmd **s)
{
    if((*s)->infd != 0)
        close((*s)->infd);
    if((*s)->outfd != 1)
        close((*s)->outfd);
}
void pipe_line(t_exec_cmd **s, t_shell  **data)
{
    int prev[2] = {-1, -1};
    int root[2];
    t_exec_cmd *cmd = (*s);
    pid_t pid;

    while (cmd != NULL)
    {
        if (cmd->next != NULL)
            if (pipe(root) == -1)
                fail_case("pipe creation failed");
        pid = fork();
        if (pid == -1)
            fail_case("fork failed");
        if (pid == 0) 
            exic_path(prev,root,&cmd,data);
        else 
            parent_part(pid,root,prev,&cmd);
        close_files(s);
        cmd = cmd->next;
    }
    if (prev[0] != -1)
        close(prev[0]);
}
int get_exit(int sts, bool set)
{
    static int status;
    if (!set)
        status = sts;
    return (status);  
}
int exice(t_exec_cmd **cmd,int type,t_shell **info)
{
    // ft_print_stack(*cmd);
	if(type == 2)
		pipe_line(cmd,info);
	else
		exic(cmd,info);
    return 1;
}
void save_env(t_environment **env)
{
    int i;
    char **buffer;
    
    i = 0;
    while ((*env)->env[i])
        i++;
    buffer = (char **)malloc(sizeof(char *) * (i + 1));
    if (!buffer)
        return;
    i = 0;
    while ((*env)->env[i])
    {
        buffer[i] = ft_strdup((*env)->env[i]);
        if (!buffer[i])
        {
            while (--i >= 0)
                free(buffer[i]);
            free(buffer);
            return;
        }
        i++;
    }
    buffer[i] = NULL;
    // printf("wrgvD\n");
    master(0, 0);  
    (*env)->lenv = env_set(buffer);
    (*env)->env = join_to_env((*env)->lenv);
    i = 0;
    free2d(buffer);
}
// void save_env(t_environment **env)
// {
//     int i;
//     char *buffer[1024];
    
//     i = 0;
//     while((*env)->env[i])
//     {
//         buffer[i] = ft_strdup((*env)->env[i]);
//         if(!buffer[i])
//             return;
//         i++;
//     }
//     buffer[i] = NULL;
//     master(0,0);
//     (*env)->lenv = env_set(buffer);
//     free
//     (*env)->env = join_to_env((*env)->lenv);
// }
int main(int ac, char **av, char **env)
{
	char    *input;

	(void)ac;
	(void)av;
	t_shell	*data;
    char    prompt[] = "\x1B[36mminishell\x1B[0m : ";
    int flage;
	data = init(env);
	if(!data)
		return 1;
	while (1)
	{ 
		input = readline(prompt);
		if(*input)
		{
			add_history(input);
            flage = pars(&data,input);
            if(flage != -1)
                exice(&data->cmd,flage,&data);
            
		}
        free(input);
        save_env(&data->env);
	}
    // free_data(&data);./m 
	return (0);
}

