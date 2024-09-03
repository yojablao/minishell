/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:30 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/03 19:50:40 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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


typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_environment
{
    char    	*env;
    char			*value;
    char 				*var;
    struct  s_environment *next;
}	t_environment;
char    *ft_my_malloc( size_t len);
int		syntax(char *str);
void	ft_full_list(t_list **a, char *s);
void	ft_print_stack(t_list *a);
//int syntax_ok(char *str);
int    ft_check_Quotes(char *str);
void	ft_free_stack(t_list *a);
void	skip_betw_quotes(char *str, size_t *i);
char	*skip_betw_quotes2(char *str);

#endif