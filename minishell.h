/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:30 by hamrachi          #+#    #+#             */
/*   Updated: 2024/08/23 09:08:51 by hamrachi         ###   ########.fr       */
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

typedef struct s_correc
{
    size_t i;
    size_t j;
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
int syntax_ok(char *str);
int    ft_check_Quotes(char *str);
#endif