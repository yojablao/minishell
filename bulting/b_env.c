#include "../minishell.h"

int    env_build(t_env *env)
{
    // int i = 0;

    while (env)
    {

        if(env->valid == 1)
        {
            ft_putstr_fd(env->key,1);
            ft_putstr_fd("=",1);
            ft_putstr_fd(env->value,1);
            ft_putstr_fd("\n",1);
        }
        env = env->next;
    }
    return 0;
    
}
// void add_to_env(char *new_value,t_env *env,char *the_key)
// {
    
//     while()

    

// }