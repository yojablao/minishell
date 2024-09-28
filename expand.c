#include "minishell.h"
char *expand(char *s, char **envo)
{
    t_env *env = env_set(envo);
    // if (!env)
    //     return NULL;
    
    if (s[0] == '$')
        s++;
    // printf("lol: %s", s);
    while (env)
    {
        // printf("Checking environment key: %s\n", env->key);
        if (!ft_strcmp(env->key, s))
        {
            // printf("Match found! Value: %s\n", env->value);
            char *result = ft_strdup(env->value);
            if (!result)
                return NULL; 
            return result;
        }
        env = env->next;
    }
    // printf("No match found for: %s\n", s);
    return NULL;
}
// t_env     *env_set(char **envi)
// {
//     t_env    *env = NULL;
//     t_env    *new_env = NULL;
//     t_env    *tmp = NULL;

//     int i = 0;
//     int j;
//     if(!envi)
//         return NULL;
//     while(envi[i])
//     {
//         j = 0;
//         while(envi[i][j])
//         {
//             if(envi[i][j] == '=')
//             {
//                 new_env = malloc(sizeof(t_env));
//                 if(!new_env)
//                     return NULL;
//                 envi[i][j] = '\0';
//                 new_env->key = ft_strdup(&envi[i][0]);
//                 new_env->value= ft_strdup(&envi[i][j + 1]);
//                 new_env->next = NULL;
//                 if(tmp == NULL)
//                     env = new_env;
//                 else
//                     tmp->next = new_env;
//                 tmp = new_env;
//                 envi[i][j] = '=';
//                 break;

//             }
//             j++;
//         }
//         i++;
//     }
//     return (env);
// }

char    *find_comond(char *comond,char **env)
{
    int i = 0;
    t_env    *tmp ;
    char    *path;
    char    *add;
    char    **fullpath;

    
    tmp = env_set(env);
    while(tmp !=   NULL && (ft_strcmp(tmp->key,"PATH")) != 0)
    {
        if((ft_strcmp(tmp->key,"PATH")) == 0)
            break;
        else
            tmp = tmp->next;
    }
    if((ft_strcmp(tmp->key, "PATH")) == 0)
    {
        // printf("%s\n",tmp->content);
        fullpath = ft_split(tmp->value, ':');
        while(fullpath[i] != NULL)
        {
            add = fullpath[i];
            fullpath[i] =  ft_strjoin(fullpath[i],"/");
            free(add);
            if(!fullpath[i])
                return NULL;
            path = ft_strjoin(fullpath[i],comond);
            if(!path[i])
                return NULL;
            if(!access(path, X_OK))
            {

                // printf("lololo %s\n",path);
                return(path);
            }
            i++;
        }
    }
    return (NULL);

}