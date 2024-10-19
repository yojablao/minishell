/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:50:05 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/14 21:30:51 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *expand(char *s, char **envo)
{
    t_env *env = env_set(envo);
    if (!env)
        return NULL;
    
    if (s[0] == '$')
        s++;
    while (env)
    {
        if (!ft_strcmp(env->key, s))
        {
            char *result = f_strdup(env->value);
            if (!result)
                return NULL; 
            return result;
        }
        env = env->next;
    }
    return NULL;
}
