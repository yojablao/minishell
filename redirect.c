/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:50:16 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/04 03:50:17 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int in_redirect(char *file)
{
    int fd ;
    // printf("%s\n",file);
    fd = open(file,O_RDONLY);
    // printf("%s\n",file);
    if(fd < 0)
        return -1;
    return fd;
}
int out_redirect(char *file)
{
    int fd;
    // printf("%s\n",file);
    fd = open(file,O_WRONLY | O_CREAT| O_TRUNC ,0644);
    if(fd < 0)
        return -1;
    return fd;
}
int append(char *file)
{
    int fd;
    // printf("%s\n",file);
    fd = open(file,O_WRONLY | O_CREAT|O_APPEND,0644);
    if(fd < 0)
        return -1;
    return fd;

}
