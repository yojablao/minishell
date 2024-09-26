/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/26 06:23:31 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// void	leaks()
// {
// 	system("leaks minishell");
// }
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
// void    full_list_b(t_exex_cmd **b,t_list *a)
// {
//     // t_listb **b;
//     t_list	*tmp;
//     int cnt = 0;
//     int i;

//     tmp = a;
//     while (tmp)
//     {
//         if (ft_strcmp(tmp -> content, "|") == 0)
//             cnt += 1;
//         tmp = tmp -> next;
//     }
//     tmp = a;
//     i = 0;
//     while (tmp && i <= cnt )
//     {
// 		if(tmp->content == '|')
// 		{
//         	b = malloc;
			
// 		}
//         tmp = tmp -> next;
//         i++;
//     }
// }
t_exec_cmd	*int_comond(char **env ,t_exec_cmd *s)
{
	t_exec_cmd *st;
    st = malloc(sizeof(t_exec_cmd));
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
    st->files = NULL;
    st->env = env;
	return(st);
}

int pipe_check(char *s)
{
	// t_exec_cmd *cmd = *struc;
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
    // if(k != 0)
    // {
    //     while(s[i] != '\0')
    //     {
    //         if(s[i] == '|')
    //         {
    //             int_comond(&cmd->next);
    //             if(!cmd->next)
    //                 return(-1);
	// 			cmd = cmd->next;
    //         }
    //         i++;
    //     }
	// 	cmd->next = NULL;
	// 	cmd = head;
    // }
    return(k);
}
char **init_mult_cmd(t_list *a, int p)
{
    char *tmp;
    char *line_parsed = NULL;
	char **comond;
    comond = malloc(sizeof(char **) * (p + 2));
    int k = 0;
    while(a)
    {
        if(a->stat == 0)
        {
            if (line_parsed)
            {
                comond[k] = line_parsed;
                k++;
                line_parsed = NULL;
            }
        }
        else
        {
            if (!line_parsed) 
                line_parsed = ft_strdup(a->content); 
            else
            {
                tmp = line_parsed;
                line_parsed =ft_strjoin(line_parsed ,a->content);
                free(tmp);
                
            }
            tmp = line_parsed;
            line_parsed = ft_strjoin(line_parsed ,"  ");
            free(tmp);
            printf("%s\n",line_parsed);
        }
        a = a->next;
    }
    comond[k] = NULL;
    k = 0;
        while(comond[++k])
            printf("%s\n",comond[k]);
    return (comond);
}
int pars(t_top **cmd,char *input)
{
	int i = -1;
	char **comond;
	(*cmd)->cmd = int_comond((*cmd)->env->env,(*cmd)->head);
	
	if(!(*cmd)->cmd)
		return -1;
    if(!syntax(input,cmd))
    	return -1;
	(*cmd)->head =(*cmd)->cmd;
	(*cmd)->n_pipe = pipe_check(input);
	if((*cmd)->n_pipe > 0)
	{
		comond = init_mult_cmd((*cmd)->a,(*cmd)->n_pipe);
        i = -1;
		while(comond[++i])
		{

			handel_comond(comond[i],&(*cmd)->cmd,(*cmd)->env->env);
			(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],(*cmd)->env->env);
			if(comond[i + 1] == NULL)
				break;
			(*cmd)->cmd->next = int_comond((*cmd)->env->env,(*cmd)->head);
			if(!(*cmd)->cmd->next)
				exit(150);
			(*cmd)->cmd = (*cmd)->cmd->next;
		}
		(*cmd)->cmd = (*cmd)->head;
		return(2);
	}
	handel_comond(input,&(*cmd)->cmd,(*cmd)->env->env);
	(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->cmd,(*cmd)->env->env);
		return(1);
}
void     exic(t_exec_cmd **s,char **env)
{
    pid_t pid  = fork();
        
    // filehandler(*s);
    if(pid == 0)
    {
        // printf("hire\n");
        child(s,env);
        return ;

    }
    else 
        waitpid(pid,0,0);
    
}
// bool exec_cmd(t_top **main)
// {
// 	t_exec_cmd *struc_cmnd;
// 	struc_cmnd = (*main)->cmd;
// 	while(struc_cmnd != NULL)
// 	{
		
// 	}
	
// }
// void	exic_v2();
// void	pipe_line(t_exec_cmd **s,char **env)
// {
// 	int prev[2] = {-1,-1};
// 	int fd[2];
// 	t_exec_cmd *cmd  = *s;
// 	 pid_t pid ;
// 	while(cmd != NULL)
// 	{
// 		if(!cmd->cmd)
// 	 		printf("wazebi\n");
			
// 	 	ft_print_stack(cmd);
// 		if(cmd->next != NULL)
// 		{
// 			if(pipe(fd) == -1)
// 			{
// 				exit(1);
// 			}
// 		}
// 		pid = fork();
// 		if(pid == -1)
// 			exit (1);
// 		if(pid == 0)
// 		{
// 			if(prev[0] != -1)
// 			{
// 				if(dup2(prev[0],0) == -1)
// 					exit(20);
				
// 			}
// 			if(cmd->next != NULL)
// 			{
// 				if(dup2(fd[1],1) == -1)
// 					exit(20);
// 			}
// 			close(fd[0]);
// 			close(fd[1]);
//  			if (prev[0] != -1)
// 			{
// 			 	close(prev[0]);
// 			}
				
			
// 			child(&cmd,env);
// 		}
// 		else
// 		{
// 			waitpid(pid,0,0);
// 			if(prev[0] != -1)close(prev[0]);
			
// 			prev[0] = fd[0];
// 			prev[1] = fd[1];
			
// 		}
// 		cmd = cmd->next;
// 		// printf("%s\n",cmd->cmd);/
// 	}
	
// }
void pipe_line(t_exec_cmd **s, char **env)
{
    int prev[2] = {-1, -1};
    int root[2];
    t_exec_cmd *cmd = *s;
    pid_t pid;

    while (cmd != NULL) {
        if (cmd->next != NULL) {
            if (pipe(root) == -1) {
                perror("pipe creation failed");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            if (prev[0] != -1) {
                if (dup2(prev[0], 0) == -1) {
                    perror("dup2 input redirection failed");
                    exit(EXIT_FAILURE);
                }
            }

            if (cmd->next != NULL) {
                if (dup2(root[1], 1) == -1) {
                    perror("dup2 output redirection failed");
                    exit(EXIT_FAILURE);
                }
            }

            close(root[0]);
            close(root[1]);
            if (prev[0] != -1) close(prev[0]);
            child(&cmd, env);
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, 0, 0);
            close(root[1]);
            if (prev[0] != -1) close(prev[0]);

            prev[0] = root[0];
            prev[1] = root[1];
        }
        cmd = cmd->next;
    }
}
int main(int ac, char **av, char **env)
{
	char    *input;

	(void)ac;
	(void)av;
	(void)env;
	t_top	*data;
    char    prompt[] = "\x1B[36mminishell\x1B[0m : ";
	int flage;
	data = init(env);
	if(!data)
		return 1;
	// atexit(leaks);
	while (1)
	{ 
		input = readline(prompt);
		if (input ==  NULL || !*input)
			return (free(input),1);
		else
		{
			add_history(input);
			if (!syntax(input,&data))
            {
                
				printf("syntax error\n");
                continue;
            }
			if(!data->a)
				printf("data error\n");
			flage = pars(&data,input);
			if(flage == -1)
				exit(1);
			else if(flage == 2)
				pipe_line(&data->cmd,env);
			else
				exic(&data->cmd,env);
				
			// ft_print_stack(data->cmd);
			
				
		}
	}
	return (0);
}
