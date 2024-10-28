/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:06:47 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/28 20:59:28 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 0;

t_env *env_cpy(t_env *env)
{
    t_env *tmp = env;
    t_env *new = NULL;
    t_env *head = NULL;

    while (tmp)
    {
        t_env *node = malloc(sizeof(t_env));
        if (!node)
            exit(1);
        node->key = ft_strdup(tmp->key);
        node->value = ft_strdup(tmp->value);
        node->valid = tmp->valid;
        node->flage = tmp->flage;
        node->next = NULL;

        if (!new)
            head = node;
        else
            new->next = node;

        new = node;
        tmp = tmp->next;
    }
    return head;
}

t_env *env_cpy_v2(t_env *env)
{
    t_env *tmp = env;
    t_env *new = NULL;
    t_env *head = NULL;

    while (tmp)
    {
        t_env *node = master(sizeof(t_env), 1);
        if (!node)
            exit(1);

        node->key = f_strdup(tmp->key);
        node->value = f_strdup(tmp->value);
        node->valid = tmp->valid;
        node->flage = tmp->flage;
        node->next = NULL;

        if (!new)
            head = node;
        else
            new->next = node;

        new = node;
        tmp = tmp->next;
    }
    return head;
}
void free_env(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env->next;
        if (env->key)
            free(env->key);
        if (env->value)
            free(env->value);
        // if (env->valid)
        //     free(env->valid);
        free(env);
        env = tmp;
    }
}

static void save_env(t_environment **env)
{
    int i;
    char *buffer[1024];
    t_env *lenv;

    i = 0;
    while ((*env)->env[i])
    {
        buffer[i] = ft_strdup((*env)->env[i]);
        if (!buffer[i])
            return;
        i++;
    }
    buffer[i] = NULL;
    lenv = env_cpy((*env)->lenv);
    master(0, 0);
    (*env)->lenv = env_cpy_v2(lenv);
    (*env)->env = join_to_env((*env)->lenv);
    free_env(lenv);
    free2d(buffer);
}
static void process_input(char *input, t_shell **data)
{
    int flage;

    if (*input)
    {
        add_history(input);
        flage = parsing_input(data, input);
        if (g_sig == 1)
            close_open_fd_1(&(*data)->cmd);
        if (flage != -1 && g_sig == 0)
            exice(&(*data)->cmd, flage, data);
    }
}
void handling_sig(int ac)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)ac;
}
static void minishell_loop(t_shell **data, char *prompt)
{
    char *input;
    int org_in;

    signal(SIGINT, handling_sig);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        g_sig = 0;
        input = readline(prompt);
        org_in = dup(STDIN_FILENO);
        if (!input)
        {
            printf("exit");
            close(org_in);
            exit(0);
        }
        process_input(input, data);
        free(input);
        dup2(org_in, STDIN_FILENO);
        close(org_in);
        save_env(&(*data)->env);
    }
}

int main(int ac, char **av, char **env)
{
    t_shell *data;
    char prompt[] = "\001\033[1;32m\002minishell\001\033[0m\002 : ";


    (void)ac;
    (void)av;
    data = init(env);
    if (!data)
        return (1);
    rl_catch_signals = 0;
    // if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
    // {
    //     write(2, "not a tty!\n", 12);
    //     return (0);
    // }
    minishell_loop(&data, prompt);

    return (0);
}