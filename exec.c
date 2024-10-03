#include "minishell.h"
void    child(t_exec_cmd **cmd,char **env)
{
    filehandler(cmd);
    if ((*cmd)->cmd == NULL || (*cmd)->args == NULL) {
        perror("Command is NULL");
        exit(EXIT_FAILURE);
    }

    if (execve((*cmd)->cmd, (*cmd)->args, env) == -1)
    {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}

