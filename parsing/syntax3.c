

#include "../minishell.h"

char	*ft_handel_spaces_allocation(char *str)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = NULL;
	len2 = ft_count_operators(str);
	len1 = ft_strlen(str) + len2;
	new = ft_my_malloc(len1 + 1);
	return (new);
}

int	ft_check_quotes(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			skip_betw_quotes(str, &i);
			if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

void	ft_write_bet_quotes(char *str, char *new, int *i, int *j)
{
	char	l;

	l = str[*i];
	new[(*j)++] = str[(*i)++];
	while (str[*i])
	{
		if (str[*i] == l)
			break ;
		new[(*j)++] = str[(*i)++];
	}
	new[(*j)++] = str[(*i)];
}

void	add_spaces(char c, char *new, int *j, int v)
{
	if (v == 0)
	{
		new[(*j)++] = ' ';
		new[(*j)++] = c;
		new[(*j)++] = ' ';
	}
	else
	{
		new[(*j)++] = ' ';
		new[(*j)++] = c;
		new[(*j)++] = c;
		new[(*j)++] = ' ';
	}
}

void	ft_add_spaces(char *str, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			ft_write_bet_quotes(str, new, &i, &j);
		else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
				+ 1] == '>'))
			add_spaces(str[i++], new, &j, 1);
		else if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>'))
			add_spaces(str[i], new, &j, 0);
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
}