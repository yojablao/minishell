#include "minishell.h"

bool bulting(t_exec_cmd **s,t_shell *data)
{
	if(ft_strcmp( (*s)->args[0],"echo") == 0)
        return(echo((*s)->args),1);
    else if(ft_strcmp((*s)->args[0],"unset") == 0)
        return( un_set_builting(s,&data->env),1);
    else if(ft_strcmp((*s)->args[0],"cd") == 0)
        return(cd_builting(s,&data->env),1);
    else if(ft_strcmp((*s)->args[0],"export") == 0)
        return(export_builtin((*s)->args,&data->env),1);
    else if(ft_strcmp((*s)->args[0],"env") == 0)
        return( env_build(data->env->lenv),1);
	else if(ft_strcmp( (*s)->args[0],"env") == 0)
		return (env_build(data->env->lenv),1);
	else if(ft_strcmp( (*s)->args[0],"pwd") == 0)
		return(pwd_builting(data->env->lenv),1);
	else
		return 0;
}
bool    child(t_exec_cmd **cmd,t_shell *data)
{
	if ((*cmd)->args[0] &&(*cmd)->args[0][0] == '\2')
		return (1);
	if(!(*cmd)->args[0] || !(*cmd)->args[0][0])
		exit(0);
    filehandler(cmd);
	if(bulting(cmd,data))
	{
		add_to_env(&data->env->lenv,"_",(*cmd)->args[0],0);
		get_exit(0,0);
		exit(0);
	}
    if ((*cmd)->cmd == NULL && (*cmd)->args[0]) {
        comnond_err((*cmd)->args[0]);
        return(get_exit(127,0),exit(127),false);
    }
	else if((*cmd)->cmd == NULL && (*cmd)->args == NULL)
		exit(1);
    if(execve((*cmd)->cmd, (*cmd)->args, data->env->env) == -1)
    {
        printf("Error: %s: Permission denied\n", (*cmd)->args[0]);
		get_exit(126,0);
		exit(126);
    }
    return(EXIT_SUCCESS);
}
char	*f_strdup(const char *s1)
{
	char	*new;
	int		i;

	if (s1 == NULL)
		return (NULL);
	new = (char *)master(sizeof (char) * ft_strlen(s1) + 1,1);
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
char	*f_strjoin(char *s1, char *s2)
{
	char		*r;
	size_t		ls1;
	size_t		ls2;
	size_t		t;
	size_t		i;
	
	if (s1 == NULL && s2 == NULL)
		return (f_strdup(""));
	if (!s2 && s1)
		return(f_strdup(s1));
	if (!s1 && s2)
		return(f_strdup(s2));
	i = 0;
	ls1 = ft_strlen(s1) + 1;
	ls2 = ft_strlen(s2);
	if (ls1 == 0 && ls2 == 0)
	{
		return (f_strdup(""));
	}
	r = (char *)master((ls1 + ls2) * sizeof(char),1);
	if (!r)
	{
		return (NULL);
	}
	t = ft_strlcpy(r, s1, (ls1));
	t = ft_strlcat(r, s2, (ls1 + ls2));
	return (r);
}

char	*ft_mysep1(char *s1, char *f)
{
	char	*result;
	size_t	lword;
	size_t	i;

	result = NULL;
	lword = 0;
	while (s1[lword] && s1[lword] != f[0] && s1[lword] != f[1])
	{
		if (s1[lword] == 39 || s1[lword] == 34)
		{
			skip_betw_quotes(s1,&lword);
			lword++; 
		}
        else
			lword++;
	}
	result = ft_my_malloc(lword + 1);
	i = 0;
	while (i < lword)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**my_copy1(char **new, char *s, int x, char *f)
{
	t_member_split sp;

	sp.n = 0;
	sp.tmp = NULL;
	while (*s && sp.n < x)
	{
		while ((*s == f[0] || *s == f[1]) &&  *s)
			s++;
		if (*s != '\0')
		{
			sp.tmp = ft_mysep1(s, f);

			new[sp.n++] = sp.tmp;
		}
		while ((*s != f[0] && *s != f[1]) && *s)
		{
			if (*s == 34 || *s == 39)
			{
				s = skip_betw_quotes2(s);
				s++;
			}
			else
				s++;
		}
	}
	new[sp.n] = NULL;
	return (new);
}


int ft_counter2(char *s, char *f)
{
    size_t i = 0;
    size_t cnt = 0;

	if(!s || !*s)
		return(0);
    while (s[i])
    {
        while ((s[i] == f[0] || s[i] == f[1] )&& s[i] != '\0')
            i++;
        if (s[i] != '\0')
        {
            cnt++;
            while (s[i] != f[0] && s[i] != f[1] && s[i] != '\0')
            {
                if (s[i] == 39 || s[i] == 34)
                {
					skip_betw_quotes(s, &i);
					i++;
				}
                else
                    i++;
            }
        }
    }
    return cnt;
}
char	**f_split(char *s, char c, char c1)
{
	char	**new;
	int		x;
	char f[2];

	if (!s)
		return (NULL);
	f[0] = c;
	f[1] = c1;
	new = NULL;
	x = ft_counter2(s, f);
	new = (char **)f_calloc(x + 1, sizeof(char *));
	if (!new)
		return (NULL);
	new = my_copy1(new, s, x, f);
	return (new);
}


