#include "minishell.h"
void    child(t_exec_cmd **s,char **env)
{
    filehandler(s);

        execve((*s)->cmd ,(*s)->args,env);
}
