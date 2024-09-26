#include "minishell.h"
t_env     *env_set(char **envi)
{
    t_env    *env = NULL;
    t_env    *new_env = NULL;
    t_env    *tmp = NULL;

    int i = 0;
    int j;
    if(!envi)
        return NULL;
    while(envi[i])
    {
        j = 0;
        while(envi[i][j])
        {
            if(envi[i][j] == '=')
            {
                new_env = malloc(sizeof(t_env));
                if(!new_env)
                    return NULL;
                envi[i][j] = '\0';
                new_env->key = ft_strdup(&envi[i][0]);
                new_env->value= ft_strdup(&envi[i][j + 1]);
                new_env->next = NULL;
                if(tmp == NULL)
                    env = new_env;
                else
                    tmp->next = new_env;
                tmp = new_env;
                envi[i][j] = '=';

                break;

            }
            j++;
        }
        i++;
    }
    return (env);
}
int count_words(char **words)
{
    int count = 0;

    while (words[count] != NULL)
    {
        count++;
    }

    return count;  
}
bool    pasabel(char *c)
{
    if(ft_strncmp(c,"<",1) == 0)
        return (false);
    if(ft_strncmp(c,"<<",2) == 0)
        return(false);
    if(ft_strncmp(c,">",1) == 0)
        return (false);
    if(ft_strncmp(c,"|",1) == 0)
    
        return (false);
    return(true);
}
bool    handel_comond(char *cmd,t_exec_cmd **comond,char **env)
{
    char **words = ft_split(cmd, ' ');
      char **args;  
    args = malloc(sizeof(char *) * (count_words(words) + 1));
    char *temp;
    int i = 0;
    int j = 0;

    while(words[i] != NULL)
    {
        if(words[i][0] == '$')
        {
            temp = words[i];
            words[i] =  expand(words[i],env);
            free(temp);
        }
        if(words[i][0] == '|')
            i++;
        else if(ft_strcmp(words[i],"<<") == 0)
        {

            (*comond)->infd =  ft_herdoc(words[++i]);
            printf("%d\n",(*comond)->infd);
            if((*comond)->infd == -1)
                return false;
        }
        else if( ft_strcmp(words[i],">") == 0)
        {
            (*comond)->outfd = out_redirect(words[++i]);
            if((*comond)->outfd == -1)
                return false;

        }
        else if(ft_strcmp(words[i],"<") == 0)
        {
            (*comond)->infd = in_redirect(words[++i]);
            if((*comond)->infd == -1)
                return false;
        }
        else
        {
            if(((i >= 1 && pasabel(words[i - 1]) == true) || i == 0 ))
            {
                args[j] = words[i];
                j++;

            }

            i++;
        }
    }
    if(!args)
        return(false);
    args[j] = NULL;
    (*comond)->args = args;
    (*comond)->cmd = words[0];
    return(args);
    
}
void filehandler(t_exec_cmd **s)
{
        // printf("%d\n",(*s)->infd);
    if ((*s)->infd != 0)
    { 
        if (dup2((*s)->infd, 0) == -1) {
            perror("dup2 input redirection failed");
            exit(EXIT_FAILURE);
        }
        close((*s)->infd); 
    }

    // Handle output redirection
    if ((*s)->outfd != 1) {  // If outfd is not stdout (1), redirect output
        // printf(";olol\n");
        if (dup2((*s)->outfd, 1) == -1) {
            perror("dup2 output redirection failed");
            exit(EXIT_FAILURE);
        }
        close((*s)->outfd);  // Close the original output file descriptor
    }
}