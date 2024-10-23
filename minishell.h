/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:30 by hamrachi          #+#    #+#             */
/*   Updated: 2024/10/22 18:25:38 by yojablao         ###   ########.fr       */
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
#define defaultpath "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."


typedef struct s_env
{
    char *key;
    char *value;
    bool valid;
    struct s_env *next;
} t_env;

typedef struct s_exec_cmd {
    struct s_exec_cmd *next;
    struct s_exec_cmd *head;
    int infd;
    int outfd;
    char *cmd;
    char **args;
    bool builting;
    // char **env;
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

typedef struct s_malloc
{
    void *ptr;
    
    struct s_malloc *next;
} t_malloc;



typedef struct s_environment
{
    char    	**env;
    t_env       *lenv;
    struct  s_environment *next;
}	t_environment;

typedef struct top
{
    t_list  *a;
    int     dup_stdin;
    t_exec_cmd *cmd;
    t_environment   *env;
    char   **env_ini;
    t_exec_cmd *head;
    int     n_pipe;
    int     *curr;
    int     *prev;
}t_shell;
 
t_list	*f_lstnew(void *content);
char    *ft_my_malloc( size_t len);
// void	ft_free(t_list *a, char *s1, char *s2);
int		syntax(char *str,t_shell ** cmd);
void	ft_full_list(t_list **a, char *s , int c);
void	ft_print_stack(t_exec_cmd *a);
void f(void *content);
void    ft_printf_a(t_list *a);
int    ft_check_Quotes(char *str);
//int syntax_ok(char *str);
void	ft_free_stack(t_list *a);
void	skip_betw_quotes(char *str, size_t *i);
char	*skip_betw_quotes2(char *str);
int     ft_check_grammer(t_list *a);
/////////added
t_env     *env_set(char **envi);
char	*f_substr(char const *s, unsigned int start, size_t len);

char    *find_comond(char *comond,t_env **env);
void free2d(char **s);
int out_redirect(char *file);
int in_redirect(char *file);
// bool    handel_comond(char *cmd,t_exec_cmd **comond,char **env);
char *expand(char *s,char **envo);
int    ft_herdoc(char *del,char **env);
void filehandler(t_exec_cmd **s);
bool    child(t_exec_cmd **s,t_shell *data);
int append(char *file);
char **ft_joinlist(t_list *a,t_environment **env);
int count_words(char **words);
bool    pasabel(char *c);
void    *master(size_t size, int flag);
char	*f_strdup(const char *s1);
char	*f_strjoin(char *s1, char *s2);
char	**f_split(char *s, char c);
void	*f_calloc(size_t count, size_t size);
t_shell   *init(char **envi);
int pars(t_shell **cmd,char *input);
t_exec_cmd	*aloc_comond(t_exec_cmd *s);
char **init_mult_cmd(t_list *a, int p);
void free_data(t_shell **shell);
bool handel_redirect(int *j,char **words ,t_exec_cmd **comond,char **env);
bool init_pipe_line(t_shell **cmd);

bool comond_init(t_shell **cmd);
///builting
void add_to_env(t_env **envi, char *key,char *content,bool add);
int export_builtin(char **str, t_environment **env);
int    env_build(t_env *env);
void echo(char **input);
char *extract_value(t_env *env,char *key);
bool    un_set(char *s,t_environment **env);
bool    un_set_builting(t_exec_cmd **s,t_environment **env);
int size_env(t_env *tmp);
char	*ft_get_env(t_shell *data, char *key);
char **join_to_env(t_env *env);
void pwd_builting(t_env *l);
void cd_builting(t_exec_cmd **s,t_environment **env);
int check_internal_builtins(t_exec_cmd **s,t_environment **env);
// char **expand_f(char **s,t_env *env);
// char *expand_chesk(char *s,t_env *env);
size_t	f_strlen2d(char **str);
char *ft_expand(char *s, char **envi);
// char *ft_expand(char *s, t_env *env);
bool    handel_comond(char **words,t_exec_cmd **comond,t_environment **env);
int get_exit(int sts, bool set);
char *ft_expand1(char *s, char **envi);
void add_key_env(t_env **env, char *key, char *value);
void comnond_err(char *s);

#endif