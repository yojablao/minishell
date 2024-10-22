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
    filehandler(cmd);
	if(bulting(cmd,data))
	{
		add_to_env(&data->env->lenv,"_",(*cmd)->args[0],0);
		get_exit(0,0);
		exit(0);
	}
    if ((*cmd)->cmd == NULL && (*cmd)->args == NULL) {
        perror("Command is NULL");
        return(get_exit(127,0),exit(127),false);
    }

    if(execve((*cmd)->cmd, (*cmd)->args, data->env->env) == -1)
    {
        printf("Error: %s: Permission denied\n", (*cmd)->args[0]);
		get_exit(1,0);
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
// char	*f_strjoin(char const *s1, char const *s2)
// {
// 	char		*r;
// 	size_t		ls1;
// 	size_t		ls2;
// 	size_t		t;
// 	size_t		i;

// 	if (s1 == NULL && s2 == NULL)
// 		return (NULL);
// 	if (!s1 && s2)
// 		return(f_strdup(s2));
// 	if (s1 && !s2)
// 		return(f_strdup(s1));
// 	i = 0;
// 	ls1 = ft_strlen(s1) + 1;
// 	ls2 = ft_strlen(s2);
// 	if (ls1 == 0 && ls2 == 0)
// 	{
// 		return (f_strdup(""));
// 	}
// 	r = (char *)master((ls1 + ls2) * sizeof(char),1);
// 	if (!r)
// 		return (NULL);
// 	t = ft_strlcpy(r, s1, (ls1));
// 	t = ft_strlcat(r, s2, (ls1 + ls2));
// 	return (r);
// }

// static char	*sub(const char *s, char *str, size_t start, size_t size)
// {
// 	size_t	i;

// 	if (str == 0)
// 		return (NULL);
// 	i = 0;
// 	while (start < size)
// 	{
// 		str[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// static void	free_it(char **str, ssize_t	l)
// {
// 	while (l >= 0)
// 		free (str[l--]);
// 	free (str);
// }

// static size_t	count_word(const char *s, char c)
// {
// 	int		i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c && s[i])
// 			i++;
// 		if (s[i])
// 			count++;
// 		while (s[i] != c && s[i])
// 			i++;
// 	}
// 	return (count);
// }

// static ssize_t	norm(const char *s, char c, char **str, size_t i)
// {
// 	size_t	start;
// 	size_t	l;

// 	l = 0;
// 	start = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			start = i;
// 			while (s[i] && s[i] != c)
// 				i++;
// 			str[l] = (char *)master(((i - start) + 1) * sizeof(char),1);
// 			if (str[l] == NULL)
// 			{
// 				free_it(str, l);
// 				return (-1);
// 			}
// 			str[l] = sub(s, str[l], start, i);
// 			l++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (l);
// }

// char	**f_split(char *s, char c)
// {
// 	char	**str;
// 	ssize_t	l;
// 	size_t	i;
// 	size_t	word_count;

// 	if (!s)
// 		return (NULL);
// 	word_count = count_word (s, c);
// 	str = master ((word_count + 1) * sizeof(char *),1);
// 	if (str == NULL)
// 		return (NULL);
// 	i = 0;
// 	l = norm(s, c, str, i);
// 	if (l == -1)
// 		return (NULL);
// 	str[l] = NULL;
// 	return (str);
// }
char	*f_strjoin(char *s1, char *s2)
{
	//printf("here spit\n");
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

char	*ft_mysep1(char *s1, char c)
{
	char	*result;
	size_t	lword;
	size_t	i;

	result = NULL;
	lword = 0;
	while (s1[lword] && s1[lword] != c)
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

char	**my_copy1(char **new, char *s, int x, char c)
{
	t_member_split sp;

	sp.n = 0;
	sp.tmp = NULL;
	while (*s && sp.n < x)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			sp.tmp = ft_mysep1(s, c);

			new[sp.n++] = sp.tmp;
		}
		while (*s != c && *s)
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

char	**f_split(char *s, char c)
{
	char	**new;
	int		x;

	if (!s)
		return (NULL);
	new = NULL;
	x = ft_counter(s, c);
	new = (char **)f_calloc(x + 1, sizeof(char *));
	if (!new)
		return (NULL);
	new = my_copy1(new, s, x, c);
	return (new);
}


