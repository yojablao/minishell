/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:11:47 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:13:54 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_environment	*env_setup(char **envi)
{
	t_environment	*env;

	env = malloc(sizeof(t_environment));
	if (!env)
		return (NULL);
	if (!*envi)
	{
		env->env = creat_env();
		env->lenv = env_set(env->env);
		add_key_env(&env->lenv, "PATH", DEFAULT_PATH);
		env->env = join_to_env(env->lenv);
	}
	else
	{
		env->lenv = env_set(envi);
		env->lenv->flage = 0;
		update_shell_lvl(&env->lenv);
	}
	if (!env->lenv)
		return (NULL);
	env->env = join_to_env(env->lenv);
	return (env);
}

t_shell	*init(char **envi)
{
	t_shell	*data;

	data = malloc(sizeof(t_shell));
	if (!data)
		return (NULL);
	data->env = env_setup(envi);
	if (!data->env)
		return (free(data), NULL);
	data->cmd = NULL;
	return (data);
}

char	**init_mult_cmd(t_list *a, int p)
{
	char	*tmp;
	char	*line_parsed;
	char	**comond;

	line_parsed = NULL;
	comond = master(sizeof(char **) * (p + 2), 1);
	while (a)
	{
		if (a->content[0] != '|' || a->next != NULL)
		{
			if (!line_parsed)
				line_parsed = f_strdup(a->content);
			else
			{
				tmp = line_parsed;
				line_parsed = f_strjoin(line_parsed, a->content);
			}
			tmp = line_parsed;
			line_parsed = f_strjoin(line_parsed, " ");
		}
		a = a->next;
	}
	if (line_parsed)
		comond = f_split(line_parsed, '|', '|');
	return (comond);
}

t_exec_cmd	*aloc_comond(t_exec_cmd *s)
{
	t_exec_cmd	*st;

	st = master(sizeof(t_exec_cmd), 1);
	if (!(st))
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	if (!s)
		s = st->head;
	else
		st->head = s;
	st->infd = 0;
	st->outfd = 1;
	st->next = NULL;
	st->cmd = NULL;
	st->args = NULL;
	st->builting = false;
	return (st);
}

void	comnond_err(char *s, t_env *env)
{
	char	*tmp;

	tmp = extract_value(env, "PATH");
	if (tmp)
	{
		ft_putstr_fd("minishell:  ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell:  ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
	}
}
