/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/22 16:46:52 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void close_open_fd(t_shell *data)
{
    t_exec_cmd *cmd = data->cmd;
    while(cmd)
    {
        if(cmd->infd != 0)
            close(data->cmd->infd);
        if(cmd->outfd != 1)
            close(cmd->outfd);
        cmd = cmd->next;
    }
}

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
    {
        waitpid(pid,&status,0);
        // if (WIFEXITED(status))
        //     status = WEXITSTATUS(status);
        // else if (WIFSIGNALED(status))
        // {
        //     if (WTERMSIG(status) == SIGQUIT)
        //         return (printf("Quit: 3\n"), WEXITSTATUS(status) + 128);
        //     else if (WTERMSIG(status) == SIGINT)
        //         return (printf("\n"), WEXITSTATUS(status) + 128);
        // }
    }
    return(0);
}

void    pipe_handle(t_shell *sh, int curr_cmd)
{
    if (curr_cmd == 0)
        sh->prev = NULL;
    if (curr_cmd == sh->n_pipe)
        sh->curr = NULL;
}
void dup_pipe(t_shell *data, int curr_cmd)
{
    if (curr_cmd > 0)
    {
        if (dup2(data->prev[0], STDIN_FILENO) == -1)
            ft_putstr_fd("wa222\n", 2);
    }
    if (curr_cmd < data->n_pipe)
    {
        if (dup2(data->curr[1], STDOUT_FILENO) == -1)
            ft_putstr_fd("wa333\n", 2);
    }
    if (data->curr)
    {
        close(data->curr[0]);
        close(data->curr[1]);
    }
    if (data->prev)
    {
        close(data->prev[0]);
        close(data->prev[1]);
    }
}
void setup_pipe_and_fork(t_exec_cmd *cmd, t_shell *data, int curr_cmd)
{
    pid_t pid;
    if (cmd->next != NULL)
    {
        if (pipe(data->curr) == -1)
            fail_case("pipe creation failed");
    }
    pid = fork();
    if (pid == -1)
        fail_case("fork failed");
    if (pid == 0)
    {
        pipe_handle(data, curr_cmd);
        dup_pipe(data,curr_cmd);
        child(&cmd, data);
        exit(0);
    }
}
void close_ans_update(t_shell **data, int curr_cmd)
{
        if ((*data)->prev[0] != -1)
        {
            close((*data)->prev[0]);
            close((*data)->prev[1]);
        }
        if (curr_cmd != (*data)->n_pipe)
        {
            (*data)->prev[0] = (*data)->curr[0];
            (*data)->prev[1] = (*data)->curr[1];
        }
    
}
void pipe_line(t_exec_cmd **s, t_shell  **data)
{
    int curr[2];
    int prev[2];
    int curr_cmd;
    t_exec_cmd *cmd = (*s);

    prev[0] = -1;
    prev[1] = -1;
    curr[0] = -1;
    curr[1] = -1;
    curr_cmd = 0;
    (*data)->curr = curr;
    (*data)->prev = prev;
    while(cmd != NULL)
    {
        setup_pipe_and_fork(cmd, *data, curr_cmd);
        close_ans_update(data,curr_cmd);
        curr_cmd++;
        cmd = cmd->next; 
    }
    while(wait(NULL) > 0);
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
    close_open_fd((*info));
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
//=-=--=-=

int main(int ac, char **av, char **env)
{
    char    *input = NULL;
    t_shell *data;
    int     flage;
    int     stdin_backup = -1;
    char    prompt[] = "\x1B[36mminishell\x1B[0m : ";

    (void)ac;
    (void)av;
    // while(1){}
    data = init(env);
    if (!data)
        return 1;
    
    while (1)
    {
        stdin_backup = dup(STDIN_FILENO);
        if (stdin_backup == -1)
        {
            perror("dup");
            break;
        }
        input = readline(prompt);
        if (!input)
        {
            if (stdin_backup != -1)
            {
                dup2(stdin_backup, STDIN_FILENO);
                close(stdin_backup);
            }
            continue; 
        }

        if (*input)
        {
            add_history(input);
            flage = pars(&data, input);
            if (flage != -1)
                exice(&data->cmd, flage, &data);
        }

        // Restore original stdin after command execution
        if (stdin_backup != -1)
        {
            dup2(stdin_backup, STDIN_FILENO);
            close(stdin_backup);
        }

        free(input);
    }

    // free_data(&data);
    return (0);
}

//=-=-=-=-=-
// int main(int ac, char **av, char **env)
// {
// 	char    *input = NULL;

// 	(void)ac;
// 	(void)av;
// 	t_shell	*data;
//     // char    prompt[2000] = "\001\033[93m\002Minishell ⌁ \001\033[30m\033[0m\002";
//     int flage;
// 	data = init(env);
// 	if(!data)
// 		return 1;
// 	while (1)
// 	{
// 		if(input && *input)
// 		{
// 			add_history(input);
//             flage = pars(&data,input);
//             if(flage != -1)
//                 exice(&data->cmd,flage,&data); 
//             free(input);
// 		}
// 		input = readline("lol :");
        
// 	}
//     // free_data(&data);
// 	return (0);
// }
