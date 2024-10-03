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
            char *result = ft_strdup(env->value);
            if (!result)
                return NULL; 
            return result;
        }
        env = env->next;
    }
    return NULL;
}

char    *find_comond(char *comond,char **env)
{
    int i = 0;
    t_env    *tmp ;
    char    *path;
    char    *add;
    char    **fullpath;

    
    tmp = env_set(env);
    if(ft_strchr(comond,'/'))
        return(comond);
    while(tmp !=   NULL && (ft_strcmp(tmp->key,"PATH")) != 0)
    {
        if((ft_strcmp(tmp->key,"PATH")) == 0)
            break;
        else
            tmp = tmp->next;
    }
    if((ft_strcmp(tmp->key, "PATH")) == 0)
    {
        fullpath = ft_split(tmp->value, ':');
        while(fullpath[i] != NULL)
        {
            add = fullpath[i];
            fullpath[i] =  f_strjoin(fullpath[i],"/");
            free(add);
            if(!fullpath[i])
                return NULL;
            path = f_strjoin(fullpath[i],comond);
            if(!path[i])
                return NULL;
            if(!access(path, X_OK))
                return(path);
            i++;
        }
    }
    return (NULL);

}