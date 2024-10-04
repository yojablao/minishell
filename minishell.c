/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/04 03:59:01 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	leaks()
{
	system("leaks minishell");
}

void     exic(t_exec_cmd **s,char **env)
{
    pid_t pid  = fork();

    if(pid == 0)
    {
        child(s,env);
        return ;
    }
    else 
        waitpid(pid,0,0);

}

void pipe_line(t_exec_cmd **s, char **env)
{
    int prev[2] = {-1, -1};
    int root[2];
    t_exec_cmd *cmd = (*s);
    pid_t pid;

    while (cmd != NULL)
    {
        if (cmd->next != NULL)
        {
            if (pipe(root) == -1)
            {
                perror("pipe creation failed");
                exit(EXIT_FAILURE);
            }
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) 
        {
            if (prev[0] != -1)
            {
                if (dup2(prev[0], STDIN_FILENO) == -1)
                {
                    perror("dup2 input redirection failed");
                    exit(EXIT_FAILURE);
                }
                close(prev[0]);
            }
            if (cmd->next != NULL)
                if (dup2(root[1], STDOUT_FILENO) == -1)
                    exit(EXIT_FAILURE);
            if (prev[1] != -1) close(prev[1]);
            close(root[0]);
            close(root[1]);
            child(&cmd, env);
            exit(EXIT_FAILURE); 
        }
        else 
        {
            waitpid(pid, 0, 0);
            if (cmd->next != NULL)
                close(root[1]);
            if (prev[0] != -1)
                close(prev[0]);
            prev[0] = root[0];
            prev[1] = root[1];
        }

        cmd = cmd->next;
    }
    if (prev[0] != -1)
        close(prev[0]);
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
			flage = pars(&data,input);
			if(flage == -1)
				continue;
			else if(flage == 2)
				pipe_line(&data->cmd,env);
			else
				exic(&data->cmd,env);
		}
        free(input);
        master(0,0);
	}
	return (0);
}
