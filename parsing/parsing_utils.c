/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:28:05 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/04 17:25:43 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_cmd(char *comond, char *value)
{
	char	*path;
	char	**fullpath;
	int		i;

	i = -1;
	if(!access(comond,X_OK))
		return(comond);
	fullpath = f_split(value, ':', ':');
	while (fullpath[++i] != NULL)
	{
		fullpath[i] = f_strjoin(fullpath[i], "/");
		if (!fullpath[i])
			return (NULL);
		path = f_strjoin(fullpath[i], comond);
		if (!path[i])
			return (NULL);
		if (!access(path, F_OK))
			return (path);
	}
	return (NULL);
}

size_t	f_strlen2d(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	handel_comond(char **words, t_exec_cmd **comond, t_environment **env)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = master(sizeof(char *) * (count_words(words) + 1), 1);
	while (words[i] != NULL)
	{
		if (!handel_redirect(&i, words, comond, env) && g_sig != -1337)
		{
			close_open_fd(comond);
			return (false);
		}
		else if (words[i] != NULL)
		{
			if (i == 0 || (i >= 1 && pasabel(words[i - 1]) == true))
				args[j++] = words[i];
			i++;
		}
	}
	args[j] = NULL;
	(*comond)->args = args;
	return (true);
}
