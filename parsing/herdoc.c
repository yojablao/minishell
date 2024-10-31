/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:33 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 12:18:14 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	hrdc_sig(int sig)
{
	(void)sig;
	close(0);
	get_exit(1, false);
	g_sig = 1;
}

char	*heredoc_loop(char *del, t_environment **env, bool flage)
{
	char	*line;
	char	*fullline;
	char	*tmp;

	fullline = f_strdup("");
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
	return (fullline);
}

static char	*read_it(char *del, int *fd, t_environment **env, char *file)
{
	char	*fullline;
	bool	flage;

	flage = check_qoutes(del);
	if (flage == false)
		f(del);
	if (g_sig == 1)
		return (NULL);
	*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
		perror("open fail \n");
	signal(SIGINT, handling_sig);
	signal(SIGINT, hrdc_sig);
	fullline = heredoc_loop(del, env, flage);
	return (fullline);
}

int	ft_herdoc(char *del, t_environment **env)
{
	char	*fullline;
	int		fd;
	char	*s;
	char	*indx;

	indx = ft_itoa((*env)->lenv->flage);
	if (!del)
		del = f_strdup("");
	s = f_strjoin("file", indx);
	free(indx);
	fullline = read_it(del, &fd, env, s);
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
