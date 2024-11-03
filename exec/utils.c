/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:33:14 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/03 12:53:43 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

#include <stdlib.h> // Ensure to include necessary headers

char	**correct_cmd(char **args, int *j)
{
	char	**split_args;
	char	**new_args;
	int		split_count = 0;
	int		args_index = 1;
	int		new_index = 0;

	split_args = f_split(args[0], ' ', '\t');
	if (!split_args) 
		return (NULL);
	while (split_args[split_count] != NULL)
		split_count++;
	new_args = master((*j + split_count + 100) * sizeof(char *), 1);
	if (!new_args)
		return (NULL);
	for (new_index = 0; new_index < split_count; new_index++)
		new_args[new_index] = split_args[new_index];
	while (args_index < *j)
		new_args[new_index++] = args[args_index++];
	new_args[new_index] = NULL;
	*j = new_index;
	// free(split_args);

	return (new_args);
}
