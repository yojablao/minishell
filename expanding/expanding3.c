/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:37:53 by hamrachi          #+#    #+#             */
/*   Updated: 2024/11/04 16:41:09 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_noexpend(char *line, int start, int *i, char *buffer)
{
	char	*tmp;
	int		end;

	while (line[*i] && line[*i] != '$')
		(*i)++;
	end = --(*i);
	tmp = ft_strrange(line, start, end + 1);
	buffer = f_strjoin(buffer, tmp);
	return (buffer);
}

char	*ft_get_expend(char *line, int *i, t_environment **env, char *buffer)
{
	char	*tmp;
	int		end;
	int		start;

	start = *i;
	tmp = NULL;
	(*i)++;
	while (line[*i] && line[*i] != '"' && line[*i] != '\'' && line[*i] != '$')
		(*i)++;
	end = --(*i);
	tmp = ft_strrange(line, start, end + 1);
	tmp = ft_expand1(tmp, (*env)->env, (*env)->lenv);
	buffer = f_strjoin(buffer, tmp);
	return (buffer);
}

char	*ft_expend_her(char *line, t_environment **env)
{
	char	*buffer;
	int		i;
	int		start;

	buffer = NULL;
	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			start = i;
			buffer = ft_get_expend(line, &i, env, buffer);
		}
		else
		{
			start = i;
			buffer = ft_get_noexpend(line, start, &i, buffer);
		}
		i++;
	}
	return (buffer);
}
