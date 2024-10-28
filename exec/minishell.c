/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/28 08:45:19 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void close_open_fd(t_exec_cmd **data)
{

    t_exec_cmd *cmd = (*data);
    if (cmd->infd != -1 && cmd->infd != 0)
        close(cmd->infd);
    if (cmd->infd != -1 && cmd->outfd != 1)
        close(cmd->outfd);
    cmd = cmd->next;
}
void close_open_fd_1(t_exec_cmd **data)
{
    t_exec_cmd *cmd = (*data);
    while (cmd)
    {
        if (cmd->infd != -1 && cmd->infd != 0)
            close(cmd->infd);
        if (cmd->outfd != 1 && cmd->infd != -1)
            close(cmd->outfd);
        cmd = cmd->next;
    }
}

int check_internal_builtins(t_exec_cmd **s, t_environment **env)
{
    if (ft_strcmp((*s)->args[0], "exit") == 0)
        return (exit_builting((*s)->args, 1), add_to_env(&(*env)->lenv, "_", (*s)->args[0], 0), 1);
    if (ft_strcmp((*s)->args[0], "unset") == 0)
        return (un_set_builting(s, env), add_to_env(&(*env)->lenv, "_", (*s)->args[0], 0), 1);
    if (ft_strcmp((*s)->args[0], "cd") == 0)
        return (cd_builting(s, env), add_to_env(&(*env)->lenv, "_", (*s)->args[0], 0), 1);
    if (ft_strcmp((*s)->args[0], "export") == 0)
        return (export_builtin((*s)->args, env), add_to_env(&(*env)->lenv, "_", (*s)->args[0], 0), 1);
    if (ft_strcmp((*s)->args[0], "env") == 0)
        return (env_build((*env)->lenv), add_to_env(&(*env)->lenv, "_", (*s)->args[0], 0), 1);
    if (ft_strcmp((*s)->args[0], "pwd") == 0 || ft_strcmp((*s)->args[0], "PWD") == 0)
        return (pwd_builting((*env)->lenv), add_to_env(&(*env)->lenv, "_", (*s)->args[0], 0), 1);
    return (0);
}
void fail_case(char *fail)
{
    perror(fail);
    get_exit(1, 0);
    exit(EXIT_FAILURE);
}

void child_sig(int sig)
{
    if (sig == SIGQUIT)
        printf("Quit: 3");
    printf("\n");
}
int handel_wait_sig(pid_t pid)
{
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        return WEXITSTATUS(status);

    else if (WIFSIGNALED(status))
    {
        int signal = WTERMSIG(status);
        if (signal == SIGQUIT)
            printf("Quit: 3\n");
        else if (signal == SIGINT)
            printf("\n");

        return 128 + signal;
    }
    
    return 0;
}
int exic(t_exec_cmd **s, t_shell **data)
{
    pid_t pid;

    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (child(s, (*data)) == EXIT_FAILURE)
            return (1);
    }
    else
        get_exit(handel_wait_sig(pid), 0);
    return (0);
}

// void pipe_handle(t_shell *sh, int curr_cmd)
// {
//     if (curr_cmd == 0)
//         sh->prev = NULL;
//     if (curr_cmd == sh->n_pipe +1)
//         sh->curr = NULL;
// }
// void dup_pipe(t_shell *data, int curr_cmd)
// {
//     if (curr_cmd > 0)
//     {
//         if (dup2(data->prev[0], STDIN_FILENO) == -1)
//             fail_case("minishell: dup2 failed\n");
//     }
//     if (curr_cmd < data->n_pipe)
//     {
//         if (dup2(data->curr[1], STDOUT_FILENO) == -1)
//             fail_case("minishell: dup2 failed\n");
//     }
//     if (data->curr)
//     {
//         close(data->curr[0]);
//         close(data->curr[1]);
//     }
//     if (data->prev)
//     {
//         close(data->prev[0]);
//         close(data->prev[1]);
//     }
// }

// pid_t setup_pipe_and_fork(t_exec_cmd *cmd, t_shell *data, int curr_cmd)
// {
//     pid_t pid;

//     if (cmd->next != NULL)
//     {
//         if (pipe(data->curr) == -1)
//             fail_case("pipe creation failed");
//     }
//     // signal(SIGINT, child_sig);
//     // signal(SIGQUIT, child_sig);
//     signal(SIGINT, SIG_IGN);
//     pid = fork();
//     if (pid == -1)
//         fail_case("fork failed");
//     if (pid == 0)
//     {
//         signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_DFL);
//         pipe_handle(data, curr_cmd);
//         dup_pipe(data, curr_cmd);
//         child(&cmd, data);
//         // exit(0);
//     }
//     return (pid);
//     // signal(SIGINT, handling_sig);
//     // signal(SIGQUIT, SIG_IGN);
// }
// void close_ans_update(t_shell **data, int curr_cmd)
// {
//     if ((*data)->prev[0] != -1)
//     {
//         close((*data)->prev[0]);
//         close((*data)->prev[1]);
//     }
//     if (curr_cmd != (*data)->n_pipe)
//     {
//         (*data)->prev[0] = (*data)->curr[0];
//         (*data)->prev[1] = (*data)->curr[1];
//     }
// }
// void pipe_line(t_exec_cmd **s, t_shell **data)
// {
//     int curr[2];
//     int prev[2];
//     int curr_cmd;
//     int status;
//     pid_t pid;
//     t_exec_cmd *cmd = (*s);

//     prev[0] = -1;
//     prev[1] = -1;
//     curr[0] = -1;
//     curr[1] = -1;
//     curr_cmd = 0;
//     (*data)->curr = curr;
//     (*data)->prev = prev;
//     while (cmd != NULL)
//     {
//         pid = setup_pipe_and_fork(cmd, *data, curr_cmd);
//         close_ans_update(data, curr_cmd);
//         close_open_fd(&cmd);
//         curr_cmd++;
//         cmd = cmd->next;
//     }
//     cmd = (*data)->head;  // Reset to the start of the command list
//     while (cmd != NULL)
//     {
//         waitpid(pid, &status, 0);
//         cmd = cmd->next;
//     }
//     get_exit(status,0);
// }
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
int exice(t_exec_cmd **cmd, int type, t_shell **info)
{
    // ft_print_stack(*cmd);
    if (type == 2)
        pipe_line(cmd, info);
    else
    {
        exic(cmd, info);
        close_open_fd(cmd);
    }

    return 1;
}
