/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:18:35 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 12:19:34 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		free(s[i]);
}

char	*f_strtrim(char const *s1, char const *set)
{
	char	*end;
	char	*result;
	size_t	s;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (end >= s1 && ft_strchr(set, *end))
		end--;
	end += 1;
	s = ft_strlen(s1) - ft_strlen(end);
	result = (char *)master(s + 1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < s)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_get_env(t_shell *data, char *key)
{
	t_env	*temp;

	temp = data->env->lenv;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
