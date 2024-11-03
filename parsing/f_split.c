/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:56:33 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/03 12:16:02 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*f_strjoin(char *s1, char *s2)
{
	char	*r;
	size_t	ls1;
	size_t	ls2;
	size_t	t;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (f_strdup(""));
	if (!s2 && s1)
		return (f_strdup(s1));
	if (!s1 && s2)
		return (f_strdup(s2));
	i = 0;
	ls1 = ft_strlen(s1) + 1;
	ls2 = ft_strlen(s2);
	if (ls1 == 0 && ls2 == 0)
		return (f_strdup(""));
	r = (char *)master((ls1 + ls2) * sizeof(char) + 1, 1);
	if (!r)
		return (NULL);
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
			skip_betw_quotes(s1, &lword);
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
	t_member_split	sp;

	sp.n = 0;
	sp.tmp = NULL;
	while (*s && sp.n < x)
	{
		while ((*s == f[0] || *s == f[1]) && *s)
			s++;
		if (*s != '\0')
		{
			sp.tmp = ft_mysep1(s, f);
			new[sp.n++] = sp.tmp;
		}
		while ((*s != f[0] && *s != f[1]) && *s)
		{
			if (*s == 34 || *s == 39)
				s = skip_betw_quotes2(s);
			s++;
		}
	}
	new[sp.n] = NULL;
	return (new);
}

int	ft_counter2(char *s, char *f)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
	{
		while ((s[i] == f[0] || s[i] == f[1]) && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			cnt++;
			while (s[i] != f[0] && s[i] != f[1] && s[i] != '\0')
			{
				if (s[i] == 39 || s[i] == 34)
					skip_betw_quotes(s, &i);
				if(s[i] != '\0')
					i++;
			}
		}
	}
	return (cnt);
}

char	**f_split(char *s, char c, char c1)
{
	char	**new;
	int		x;
	char	f[2];

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
