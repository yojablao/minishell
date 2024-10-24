/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:33 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/24 03:04:22 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	free2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		free(s[i]);
	free(s);
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

static char	*read_it(const char *del, int *fd, char **env, bool flage)
{
	char	*fullline;
	char	*tmp;
	char	*line;

	fullline = NULL;
	*fd = open("/tmp/lo.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
		perror("open fail \n");
	while (1)
	{
		line = readline("\033[95m heredoc> \033[0m");
		tmp = line;
		if (!line || !ft_strcmp(line, (char *)del))
		{
			free(line);
			break ;
		}
		if (flage == true)
			tmp = ft_expand1(line, env);
		tmp = f_strjoin(tmp, "\n");
		free(line);
		fullline = f_strjoin(fullline, tmp);
	}
	return (fullline);
}

bool	check_qoutes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (false);
	}
	return (true);
}

int	ft_herdoc(char *del, char **env)
{
	char	*fullline;
	int		fd;
	int		flage;

	flage = check_qoutes(del);
	if (flage == false)
		f(del);
	fullline = read_it(del, &fd, env, flage);
	if (fullline)
    {
		if (write(fd, fullline, ft_strlen(fullline)) == -1)
			return (perror("Error writing to file"), close(fd), -1);
    }
	close(fd);
	fd = open("/tmp/lo.txt", O_RDONLY);
	if (fd == -1)
		return (perror("Error reopening heredoc file for reading"), -1);
	return (fd);
}
