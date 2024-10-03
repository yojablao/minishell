/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:30 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/01 19:04:32 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

#include <stdbool.h>
#include <sys/fcntl.h>
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_exec_cmd {
    struct s_exec_cmd *next;
    struct s_exec_cmd *head;
    int infd;
    int outfd;
    char *cmd;
    char **args;
    // char **files;
    char **env;
} t_exec_cmd;
typedef struct s_num_operat
{
    size_t pipe;
    size_t inp;
    size_t out;
    size_t app;
    size_t her;
    size_t len;
}   t_num_operat;

typedef struct s_member_split
{
    char *tmp;
    int n;
}   t_member_split;
typedef struct s_quotes
{
    size_t i;
    size_t q;
    size_t dq;
    size_t var;
}   t_quotes;

typedef struct s_oper
{
    size_t i;
    size_t j;
    size_t end;
} t_correc;




typedef struct s_environment
{
    char    	**env;
    t_env       *lenv;
    struct  s_environment *next;
}	t_environment;

typedef struct top
{
    t_list  *a;
    t_exec_cmd *cmd;
    t_environment   *env;
    t_exec_cmd *head;
    int     n_pipe;
}t_top;

char    *ft_my_malloc( size_t len);
void	ft_free(t_list *a, char *s1, char *s2);
void	ft_free_array(char **s1);
int		syntax(char *str,t_top ** cmd);
void	ft_full_list(t_list **a, char *s , int c);
void	ft_print_stack(t_exec_cmd *a);
void f(void *content);
void    ft_printf_a(t_list *a);
//int syntax_ok(char *str);
int    ft_check_Quotes(char *str);
void	ft_free_stack(t_list *a);
void	skip_betw_quotes(char *str, size_t *i);
char	*skip_betw_quotes2(char *str);
int     ft_check_grammer(t_list *a);
/////////added
t_env     *env_set(char **envi);
char    *find_comond(char *comond,char **env);
int out_redirect(char *file);
int in_redirect(char *file);
bool    handel_comond(char *cmd,t_exec_cmd **comond,char **env);
bool    handel_onecomond(char **cmd,t_exec_cmd **comond,char **env);
char *expand(char *s,char **envo);
int    ft_herdoc(char *del,char **env);
void filehandler(t_exec_cmd **s);
void    child(t_exec_cmd **s,char **env);
int append(char *file);
char **ft_joinlist(t_list *a);
int count_words(char **words);
bool    pasabel(char *c);

#endif