/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:30 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/01 04:13:01 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/fcntl.h>
# include <sys/stat.h>
# include <unistd.h>

# define DEFAULT_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

int			g_sig;

typedef struct s_env
{
	char					*key;
	char					*value;
	bool					valid;
	int						flage;
	struct s_env			*next;
}							t_env;

typedef struct s_exec_cmd
{
	struct s_exec_cmd		*next;
	struct s_exec_cmd		*head;
	int						infd;
	int						outfd;
	char					*cmd;
	char					**args;
	bool					builting;
}							t_exec_cmd;

typedef struct s_num_operat
{
	size_t					pipe;
	size_t					inp;
	size_t					out;
	size_t					app;
	size_t					her;
	size_t					len;
}							t_num_operat;

typedef struct s_member_split
{
	char					*tmp;
	int						n;
}							t_member_split;

typedef struct s_quotes
{
	size_t					i;
	size_t					q;
	size_t					dq;
	size_t					var;
}							t_quotes;

typedef struct s_oper
{
	size_t					i;
	size_t					j;
	size_t					end;
}							t_oper;

typedef struct s_malloc
{
	void					*ptr;
	struct s_malloc			*next;
}							t_malloc;

typedef struct s_environment
{
	char					**env;
	t_env					*lenv;
	struct s_environment	*next;
}							t_environment;

typedef struct s_shell
{
	t_list					*a;
	int						dup_stdin;
	t_exec_cmd				*cmd;
	t_environment			*env;
	char					**env_ini;
	t_exec_cmd				*head;
	int						n_pipe;
	int						*curr;
	int						*prev;
}							t_shell;

void						free_all(void **arr);
void						print_error(char *error_msg, char *identifier,
								char *command);
t_list						*f_lstnew(void *content);
char						*ft_my_malloc(size_t len);
int							syntax(char *str, t_shell **cmd);
void						ft_add_spaces(char *str, char *new);
char						*ft_handel_spaces_allocation(char *str);
size_t						ft_count_operators(char *str);
void						ft_full_list(t_list **a, char *s, int c);
void						f(void *content);
void						ft_printf_a(t_list *a);
int							ft_check_quotes(char *str);
void						ft_free_stack(t_list *a);
void						skip_betw_quotes(char *str, size_t *i);
char						*skip_betw_quotes2(char *str);
int							ft_check_grammer(t_list *a);
void						save_env(t_environment **env);

bool						internel_builting(char *s);
t_env						*env_set(char **envi);
char						*f_substr(char const *s, unsigned int start,
								size_t len);
char						*find_comond(char *comond, t_env **env);
int							out_redirect(char *file);
int							in_redirect(char *file);
int							ft_herdoc(char *del, t_environment **env);
void						filehandler(t_exec_cmd **s);
bool						child(t_exec_cmd **s, t_shell *data);
int							append(char *file);
char						**ft_joinlist(t_list **lst, t_environment **env,
								int status);
int							count_words(char **words);
bool						pasabel(char *c);
void						*master(size_t size, int flag);
char						*f_strdup(const char *s1);
char						*f_strjoin(char *s1, char *s2);
char						**f_split(char *s, char c, char c1);
void						*f_calloc(size_t count, size_t size);
t_shell						*init(char **envi);
int							handel_wait_sig(pid_t pid, int status, bool p);
int							parsing_input(t_shell **cmd, char *input);
t_exec_cmd					*aloc_comond(t_exec_cmd *s);
char						**init_mult_cmd(t_list *a, int p);
void						free_data(t_shell **shell);
bool						handel_redirect(int *j, char **words,
								t_exec_cmd **comond, t_environment **env);
bool						init_pipe_line(t_shell **cmd);
bool						comond_init(t_shell **cmd);

void						add_to_env(t_env **envi, char *key, char *content,
								bool add);
int							export_builtin(char **str, t_environment **env);
int							env_build(t_env *env);
void						echo(char **input);
char						*extract_value(t_env *env, char *key);
bool						un_set_builting(t_exec_cmd **s,
								t_environment **env);
int							size_env(t_env *tmp);
char						**join_to_env(t_env *env);
void						pwd_builting(t_env *l);
void						cd_builting(t_exec_cmd **s, t_environment **env);
int							check_internal_builtins(t_exec_cmd **s,
								t_environment **env);
size_t						f_strlen2d(char **str);
bool						handel_comond(char **words, t_exec_cmd **comond,
								t_environment **env);
int							get_exit(int sts, bool set);
void						add_key_env(t_env **env, char *key, char *value);
void						comnond_err(char *s, t_env *env);
void						exit_builting(char **args, bool flage);
void						close_open_fd(t_exec_cmd **data);
char						**correct_cmd(char **args, int *j);
void						handling_sig(int ac);
void						close_open_fd_1(t_exec_cmd **data);
//------------expanding fuctions--------//
char						*ft_expand1(char *s, char **envi, t_env *lenv);
char						*handle_d_q_content(char *tmp, int *j, t_env *env,
								char *buffer);
char						*join_buffer(char *tmp, int *j, int start,
								char *buffer);
char						*handle_single_quote(char *s, int *i, char *buffer);
char						*expanding_values(char *key, t_env *env);
int							is_valid_identifier(char *command, int mybool);
char						*f_remove_spaces(char *str);
char						*get_key(char *s);
bool						special_lt(char l);
char						*ft_strrange(char *s, int start, int end);

char						*expand_exit_status(int status);
int							checkexpand(char *s);
char						**creat_env(void);
void						update_shell_lvl(t_env **env);
void						free2d(char **s);
bool						empty_q(char *s);
char						*valid_exp(char *content, char *expanded,
								int status);
char						*find_path_cmd(char *comond, char *value);
char						*f_strtrim(char const *s1, char const *set);
char						*ft_get_env(t_shell *data, char *key);
int							exice(t_exec_cmd **cmd, int type, t_shell **info);
int							exec_builtin(t_exec_cmd **s, t_environment **env);
void						pipe_line(t_exec_cmd **s, t_shell **data);
int							execution_one(t_exec_cmd **s, t_shell **data);
void						fail_case(char *fail);
void						child_sig(int sig);
void						pipe_handle(t_shell *sh, int curr_cmd);
int							typecheck(char *word, t_exec_cmd **comond);
void						add_or_update(t_environment **env, char *s);
void						delet_from_env(t_env **envi, char *s);
int							key_exists(char *str, t_env *env);
char						*process_double_quote(char *tmp,
								t_env *env, char *buffer);

#endif
