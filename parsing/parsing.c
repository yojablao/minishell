/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:49:39 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 10:45:20 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_count(t_list *a)
{
	int	i;

	i = 0;
	while (a)
	{
		if (a->stat == 4)
			i++;
		a = a->next;
	}
	return (i);
}

static int	pipe_check(t_list *a)
{
	int	i;

	i = 0;
	while (a)
	{
		if (a->stat == 0)
			i++;
		a = a->next;
	}
	return (i);
}

static int	heredoc_pipe_check(t_shell *sh)
{
	if (heredoc_count(sh->a) > 16)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("maximum here-document count exceeded\n", 2);
		exit(2);
	}
	sh->n_pipe = pipe_check(sh->a);
	if (sh->n_pipe > 1390)
		return (ft_putstr_fd("bash: fork: Resource temporarily unavailable\n",
				2), -1);
	return (0);
}

int	parsing_input(t_shell **cmd, char *input)
{
	if (!syntax(input, cmd))
		return (get_exit(258, 0), printf("syntax error\n"), -1);
	(*cmd)->cmd = aloc_comond((*cmd)->cmd);
	(*cmd)->head = (*cmd)->cmd;
	if (!(*cmd)->cmd || !(*cmd)->a)
		return (-1);
	(*cmd)->head = (*cmd)->cmd;
	if (heredoc_pipe_check(*cmd) == -1)
		return (-1);
	if ((*cmd)->n_pipe > 0)
	{
		if (init_pipe_line(cmd) == false)
			return (-1);
		(*cmd)->cmd = (*cmd)->head;
		return (2);
	}
	else
	{
		if (comond_init(cmd) == false)
			return (-1);
		return (1);
	}
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
		if (!handel_redirect(&i, words, comond, env))
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

char	*find_pexec(char *comond, char *value)
{
	char	*path;
	char	**fullpath;
	int		i;

	i = -1;
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
