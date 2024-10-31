/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:33:14 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 11:00:15 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*f_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	char	*src;
	size_t	l;
	size_t	i;

	if (!s)
		return (NULL);
	src = (char *)s;
	l = ft_strlen(s);
	i = 0;
	if (start >= l)
		return (f_strdup(""));
	if (len > l - start)
		len = (l - start);
	new = (char *)master((len + 1) * sizeof(char), 1);
	if (!new)
		return (NULL);
	while (i < len)
		new[i++] = src[start++];
	new[i] = '\0';
	return (new);
}

int	count_words(char **words)
{
	int	count;

	count = 0;
	while (words[count] != NULL)
		count++;
	return (count);
}

bool	pasabel(char *c)
{
	if (ft_strcmp(c, "<") == 0)
		return (false);
	if (ft_strcmp(c, "<<") == 0)
		return (false);
	if (ft_strcmp(c, ">>") == 0)
		return (false);
	if (ft_strcmp(c, ">") == 0)
		return (false);
	if (ft_strcmp(c, "|") == 0)
		return (false);
	return (true);
}

char	**correct_cmd(char **args, int *j)
{
	char	**split_args;
	char	**new_args;
	int		i;
	int		k;

	i = 0;
	k = 1;
	split_args = f_split(args[0], ' ', '\t');
	while (split_args[i] != NULL)
		i++;
	new_args = master((*j + i + 1) * sizeof(char *), 1);
	k = 0;
	while (split_args[k] != NULL)
	{
		new_args[k] = split_args[k];
		k++;
	}
	k = 1;
	while (k < *j)
		new_args[i++] = args[k++];
	new_args[i] = NULL;
	*j = i;
	return (new_args);
}

void	ft_printf_a(t_list *a)
{
	t_list	*tmp;

	tmp = a;
	while (tmp)
	{
		printf("{%s}\n", tmp->content);
		tmp = tmp->next;
	}
}
