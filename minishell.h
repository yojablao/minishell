/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:30 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/03 17:32:29 by hamrachi         ###   ########.fr       */
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

typedef struct s_quotes
{
    int i;
    int q;
    int dq;
}   t_quotes;

typedef struct s_oper
{
    size_t pipe;
    size_t her;
    size_t inp;
    size_t len;
    size_t out;
    size_t app;
} t_oper;


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
int     syntax_ok(char *str);
int		ft_check_Quotes(char *str);
void	ft_full_list(t_list **a, char *s);
void	ft_free_stack(t_list *a);
#endif