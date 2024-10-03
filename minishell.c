/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/01 22:46:40 by yojablao         ###   ########.fr       */
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
t_exec_cmd	*aloc_comond(char **env ,t_exec_cmd *s)
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
    // st->files = NULL;
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
    return(k);
}
// char **init_mult_cmd(t_list *a, int p)
// {
//     char *tmp;
//     char *line_parsed = NULL;
//     char **comond;
//     int k = 0;

//     // Correct memory allocation for 'comond'
//     comond = malloc(sizeof(char *) * (p + 2));  // Allocate for an array of 'char *'
//     if (!comond)
//         return NULL; // Check for malloc failure

//     // Initialize command list
//     while (a)
//     {
//         // Combine content with spacing for stat != 0 or next is not NULL
//         if (a->stat != 0 || a->next != NULL)
//         {
//             if (!line_parsed)
//                 line_parsed = ft_strdup(a->content);  // Duplicate initial content
//             else
//             {
//                 tmp = line_parsed;
//                 line_parsed = ft_strjoin(line_parsed, a->content);  // Append content
//                 free(tmp);  // Free old line_parsed after joining

//                 tmp = line_parsed;
//                 line_parsed = ft_strjoin(line_parsed, "  ");  // Append space
//                 free(tmp);  // Free old line_parsed after joining space
//             }
//         }
//         // Store the parsed line in the command array
//         else
//         {
//             if (line_parsed)
//             {
//                 comond[k] = line_parsed;  // Store the final string
//                 k++;  // Move to the next command
//                 line_parsed = NULL;  // Reset line_parsed for the next command
//             }
//         }
//         a = a->next;  // Move to the next element in the list
//     }

//     // Ensure the command array is null-terminated
//     comond[k] = NULL;

//     return comond;  // Return the final array of commands
// }
char **init_mult_cmd(t_list *a, int p)
{
    char *tmp;
    char *line_parsed = NULL;
	char **comond;
    comond = malloc(sizeof(char **) * (p + 2));
    // int k = 0;
    while(a)
    {
        if(a->content[0] != '|' || a->next != NULL)
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
            line_parsed = ft_strjoin(line_parsed ," ");
            free(tmp);
        }
        a = a->next;
    }
    // printf("%s\n",line_parsed);
    if (line_parsed)
        comond = ft_split(line_parsed,'|');
    // k = 0;
    //     while(comond[++k])
    //         printf("%s$\n#",comond[k]);
    return (comond);
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
			handel_comond(comond[i],&(*cmd)->cmd,(*cmd)->env->env);
			(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],(*cmd)->env->env);
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
        comond = ft_joinlist((*cmd)->a);///join nodes
		handel_onecomond(comond,&(*cmd)->cmd,(*cmd)->env->env); //expand and redirection and her dok and append
		(*cmd)->cmd->cmd = find_comond((*cmd)->cmd->args[0],(*cmd)->env->env); 
        return(1);
    }
}
bool    handel_onecomond(char **words,t_exec_cmd **comond,char **env)
{
    char **args;  
    args = malloc(sizeof(char *) * (count_words(words) + 1));
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
                free(temp);
            }
        }
        else if(ft_strcmp(words[i],"<<") == 0)
        {
            (*comond)->infd =  ft_herdoc(words[++i],env);
            // printf("%d\n",(*comond)->infd);
            if((*comond)->infd == -1)
                return false;
        }
        else if( ft_strcmp(words[i],">") == 0)
        {
            (*comond)->outfd = out_redirect(words[++i]);
            if((*comond)->outfd == -1)
                return false;
        }
        else if(ft_strcmp(words[i],"<") == 0)
        {
            (*comond)->infd = in_redirect(words[++i]);
            if((*comond)->infd == -1)
                return false;
        }
        else if(ft_strcmp(words[i],">>") == 0)
        {
            (*comond)->outfd = append(words[++i]);
            if((*comond)->outfd == -1)
                return false;
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
            {
                if (dup2(root[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 output redirection failed");
                    exit(EXIT_FAILURE);
                }
            }

            if (prev[1] != -1) close(prev[1]);
            // close(root[0]);
            // close(root[1]);
            child(&cmd, env);
            exit(EXIT_FAILURE); 
        }
        else 
        {
            int s;
            waitpid(pid, &s, 0);
            if (WIFEXITED(s))
            {
                
            }
            if (cmd->next != NULL)
            {
                close(root[1]);
            }

            if (prev[0] != -1) close(prev[0]);
            prev[0] = root[0];
            prev[1] = root[1];
        }

        cmd = cmd->next;
    }
    if (prev[0] != -1) close(prev[0]);
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

				// printf("data error\n");
            // ft_printf_a(data->a);
			flage = pars(&data,input);
			if(flage == -1)
				exit(1);
			else if(flage == 2)
            {
				pipe_line(&data->cmd,env);
            }
			else
				exic(&data->cmd,env);
				
			
				
		}
	}
	return (0);
}
