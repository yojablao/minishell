#include "minishell.h"
void free2d(char **s)
{
    int i = -1;
    while(s[++i] != NULL)
        free(s[i]);
}
char *check_expand(char *line,char **env)
{
    char *tmp;
    char *expanded;
    char *fullline;

    int flage = 0;
    int i = 0;
    fullline = NULL;
    char **words = ft_split(line,' ');
    while (words[i])
    {
        if(words[i][0] == '$')
        {
            flage = 1;
            expanded = expand(words[i],env);
            tmp = fullline;
            if(!expanded)
                exit(11);
            fullline =  ft_strjoin(fullline,expanded);
            free(tmp);
        }
        else
        {
            tmp = fullline;
            fullline =  ft_strjoin(fullline,words[i]);
            free(tmp);

        }
        tmp = fullline;
        fullline =  ft_strjoin(fullline," ");
        free(tmp);
        i++;
    }
    if(flage == 1 && fullline)
        return(fullline);
    else
        return(free2d(words),free(line),fullline);
}
static char *read_it(const char *del,int *f,char **env,bool flage)
{
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
        if(!line || ft_strcmp(line ,(char *)del) == 0)
            break;
        if(flage == true)
            line = check_expand(line,env);
        tmp = line;
        line =  ft_strjoin(line,"\n");
        free(tmp);
        tmp = fullline;
        fullline =  ft_strjoin(fullline,line);
        free(tmp);
    }
    return(fullline);
}
int    ft_herdoc(const char *del,char **env)
{
    (void)env;
    char *fullline;
    int fd;
    int flage;
    if(del[0] == '$')
    {
        flage = false;
        del++;
    }
    else
        flage = true;
    fullline =read_it(del,&fd,env,flage);
    if (fullline)
    {
        if(fullline == NULL)
            exit(1);

        if (write(fd, fullline, ft_strlen(fullline)) == -1)
            return(perror("Error writing to file"),free(fullline),close(fd), -1);
        free(fullline);
    }
    else
        return (close(fd),-1);
    close(fd);
    fd = open("/tmp/lo.txt", O_RDONLY);
    if (fd == -1)
        return (perror("Error reopening heredoc file for reading"),-1);
    return fd; 
}
