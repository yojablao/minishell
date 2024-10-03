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
    // printf("hrjvgblre\n");
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
    if(ft_strcmp(c,"<") == 0)
        return (false);
    if(ft_strcmp(c,"<<") == 0)
        return(false);
    if(ft_strcmp(c,">") == 0)
        return (false);
    if(ft_strcmp(c,"|") == 0)
        return (false);
    
    return(true);
}
void ft_printf_a(t_list *a)
{
    t_list *tmp = a;
    while(tmp)
    {
        printf("%s - content\n",tmp->content);
        tmp = tmp -> next;
    }
}
char **ft_joinlist(t_list *a)
{
    if (!a) return NULL; 

    int p = ft_lstsize(a);
    char **words = malloc(sizeof(char *) * (p + 1)); 
    if (!words) return NULL; 
    int i = 0;
    while (a)
    {
        words[i] = a->content; 
        a = a->next;          
        i++;
    }
    words[i] = NULL; 

    return words; 
}
bool    handel_comond(char *cmd,t_exec_cmd **comond,char **env)
{
     char **words = ft_split(&cmd[0],' ');
      char **args;  
    args = malloc(sizeof(char *) * (count_words(words) + 1));
    char *temp;
    int i = 0;
    int j = 0;

    while(words[i] != NULL)
    {
        if(words[i][0] == '$')
        {
            if(i > 0 && pasabel(words[i-1] ))
            {
                temp = words[i];
                words[i] =  expand(words[i],env);
                free(temp);
            }

        }
        else if(ft_strcmp(words[i],"<<") == 0)
        {

            (*comond)->infd =  ft_herdoc(words[++i],env);
            // printf("%d\n",(*comond)->infd);
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
        else if(ft_strcmp(words[i],">>") == 0)
        {
            (*comond)->outfd = append(words[++i]);
            if((*comond)->outfd == -1)
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
        // printf("%d\n",(*s)->outfd);
    if ((*s)->infd != 0)
    { 
        if (dup2((*s)->infd, 0) == -1) {
            perror("dup2 input redirection failed");
            exit(EXIT_FAILURE);
        }
        close((*s)->infd); 
    }
    if ((*s)->outfd != 1) {  
        if (dup2((*s)->outfd, 1) == -1) {
            perror("dup2 output redirection failed");
            exit(EXIT_FAILURE);
        }
        close((*s)->outfd);  
    }
}
void f(void *content)
{
    char *s = (char *)content;  // Cast content to char as it's passed as void *
    int i = 0;
    int j = 0;
    int single_q = 0;
    int double_q = 0;

    while (s[i])
    {
        if (s[i] == '\'' && !double_q)
            single_q = !single_q;
        else if (s[i] == '"' && !single_q)
            double_q = !double_q;
        else
            s[j++] = s[i];  // Copy valid characters to the current position
        i++;
    }
    s[j] = '\0';  // Null-terminate at position j
}
