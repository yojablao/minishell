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
char	*f_strdup(const char *s1)
{
	char	*new;
	int		i;

	new = (char *)c_malloc(sizeof (char) * ft_strlen(s1) + 1,1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
char	*f_strjoin(char const *s1, char const *s2)
{
	char		*r;
	size_t		ls1;
	size_t		ls2;
	size_t		t;
	size_t		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 && s2)
		return(f_strdup(s2));
	i = 0;
	ls1 = ft_strlen(s1) + 1;
	ls2 = ft_strlen(s2);
	if (ls1 == 0 && ls2 == 0)
	{
		return (f_strdup(""));
	}
	r = (char *)c_malloc((ls1 + ls2) * sizeof(char),1);
	if (!r)
	{
		return (NULL);
	}
	t = ft_strlcpy(r, s1, (ls1));
	t = ft_strlcat(r, s2, (ls1 + ls2));
	return (r);
}

