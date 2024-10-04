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
	r = (char *)master((ls1 + ls2) * sizeof(char),1);
	if (!r)
	{
		return (NULL);
	}
	t = ft_strlcpy(r, s1, (ls1));
	t = ft_strlcat(r, s2, (ls1 + ls2));
	return (r);
}

static char	*ft_mysep(char *s1, char c)
{
	char	*result;
	size_t	lword;
	size_t	i;

	lword = 0;
	while (s1[lword] != c && s1[lword])
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

static char	**my_copy(char **new, char *s, int x, char c)
{
	t_member_split sp;

	sp.n = 0;
	while (*s && sp.n < x)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			sp.tmp = ft_mysep(s, c);
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
	new[sp.n] = 0;
	return (new);
}

char	**f_split(char *s, char c)
{
	char	**new;
	int		x;

	if (!s)
		return (NULL);
	x = ft_counter(s, c);
	new = (char **)f_calloc(x + 1, sizeof(char *));
	if (!new)
		return (NULL);
	new = my_copy(new, s, x, c);
	return (new);
}


