/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:25:41 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/03 18:28:29 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

int ft_counter(char *s, char c)
{
    size_t i = 0;
    size_t cnt = 0;

    while (s[i])
    {
        while (s[i] == c && s[i] != '\0')
            i++;
        if (s[i] != '\0')
        {
            cnt++;
            while (s[i] != c && s[i] != '\0')
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
char	*ft_mysep(char *s1, char c)
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
	printf("lword = %zu\n",lword);
	result = (char *)malloc(lword + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < lword)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	printf("result == %s\n",result);
	return (result);
}

char	**ft_frees(char **new, int l)
{
	int	i;

	i = 0;
	while (i < l)
	{
		free(new[i]);
		i++;
	}
	free (new);
	return (NULL);
}

char	**my_copy(char **new, char *s, int x, char c)
{
	char	*tmp;
	int		n;

	n = 0;
	while (*s && n < x)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			tmp = ft_mysep(s, c);
			if (tmp == NULL)
				return (ft_frees(new, n));
			else
				new[n++] = tmp;
		}
		printf("here\n");
		while (*s != c && *s)
			s++;
	}
	new[n] = 0;
	return (new);
}

char	**ft_split(char *s, char c)
{
	char	**new;
	int		x;

	if (!s)
		return (NULL);
	x = ft_counter(s, c);
	printf("x = %d\n", x);
	new = (char **)ft_calloc(x + 1, sizeof(char *));
	if (!new)
		return (NULL);
	new = my_copy(new, s, x, c);
	return (new);
}
