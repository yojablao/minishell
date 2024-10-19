/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:33 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/18 10:21:11 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void free2d(char **s)
{
    int i = -1;
    while(s[++i] != NULL)
        free(s[i]);
    free(s);
}

char	*ft_get_env(t_shell *data, char *key)
{
	t_env	*temp;

	temp = data->env->lenv;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char *check_expand(char *line,char **env)
{
    char *expanded;
    char *fullline;

    int flage = 0;
    int i = 0;
    fullline = NULL;
    char **words = f_split(line,' ');
    while (words[i])
    {
        if(words[i][0] == '$')
        {
            flage = 1;
            expanded = expand(words[i],env);
            if(!expanded)
                exit(11);
            fullline =  f_strjoin(fullline,expanded);
        }
        else
            fullline =  f_strjoin(fullline,words[i]);
        fullline =  f_strjoin(fullline," ");
        i++;
    }
    if(flage == 1 && fullline)
        return(fullline);
    else
        return(fullline);
}
static char *read_it(const char *del,int *f,char **env,bool flage)
{
    (void)env;
    (void)flage;
    char    *fullline;
    char    *tmp;
    char    *line;
    int     fd;

    fullline = NULL;
    fd = open("/tmp/lo.txt",O_CREAT | O_RDWR | O_TRUNC  ,0644);
    *f =fd;
    while(1)
    {
        line = readline("\033[95m heredoc> \033[0m");
        if(!line)
            break;
        if(ft_strcmp(line ,(char *)del) == 0)
        {
            free (line);
            break;
        }
        if(flage == true)
            tmp = check_expand(line,env);
        tmp =  f_strjoin(tmp,"\n");
        free(line);
        fullline =  f_strjoin(fullline,tmp);
    }
    return(fullline);
}

bool     check_qoutes(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        if (str[i] == '\'' || str[i] == '\"')
            return (false);
    return (true);
}
int    ft_herdoc(char *del,char **env)
{
    (void)env;
    char *fullline;
    int fd;
    int flage;
    // int i;


    flage = check_qoutes(del);
    if (flage == false)
        f(del);
    fullline = read_it(del,&fd,env,flage);
    if (fullline)
    {
        if(fullline == NULL)
            exit(1);
        if (write(fd, fullline, ft_strlen(fullline)) == -1)
            return(perror("Error writing to file"),close(fd), -1);
    }
    close(fd);
    fd = open("/tmp/lo.txt", O_RDONLY);
    if (fd == -1)
        return (perror("Error reopening heredoc file for reading"),-1);
    return fd; 
}
