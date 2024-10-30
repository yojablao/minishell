/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:33 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/30 17:47:15 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			g_sig;

void	free2d(char **s)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		free(s[i]);
	// free(s);
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

void	hrdc_sig(int sig)
{
	(void)sig;
	close(0);
	get_exit(1, false);
	g_sig = 1;
}

static char	*read_it(const char *del, int *fd, t_environment **env, bool flage,char *file)
{
	char	*fullline;
	char	*tmp;
	char	*line;

	fullline = NULL;
	if (g_sig == 1)
		return (NULL);
	*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
		perror("open fail \n");
	signal(SIGINT, hrdc_sig);
	while (1)
	{
		line = readline("\033[95m heredoc> \033[0m");
		tmp = line;
		if (!line || (ft_strcmp(line, (char *)del) == -1 && !*line)
			|| !ft_strcmp(line, (char *)del))
		{
			free(line);
			break ;
		}
		if (flage == true)
			tmp = ft_expand1(line, (*env)->env, (*env)->lenv);
		tmp = f_strjoin(tmp, "\n");
		free(line);
		fullline = f_strjoin(fullline, tmp);
	}
	signal(SIGINT, handling_sig);
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

int	ft_herdoc(char *del, t_environment **env)
{
	char	*fullline;
	int		fd;
	int		flage;
	char 	*s;
	char 	*indx;

	indx = ft_itoa((*env)->lenv->flage);
	if (!del)
		del = f_strdup("");
	flage = check_qoutes(del);
	s = f_strjoin("file",indx);
	free(indx);
	if (flage == false)
		f(del);
	fullline = read_it(del, &fd, env, flage,s);
	if (fullline)
	{
		if (write(fd, fullline, ft_strlen(fullline)) == -1)
			return (perror("Error writing to file"), close(fd), -1);
	}
	close(fd);
	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (perror("Error reopening heredoc file for reading"), -1);
	return (fd);
}
