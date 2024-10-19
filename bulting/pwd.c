#include "../minishell.h"


void pwd_builting(t_env *l)
{

    char BUFFER[1024];
    char *path;

    path = getcwd(BUFFER,sizeof(BUFFER));
    if(path == NULL)
        path = extract_value(l,"PWD");
    printf("%s\n",path);
}