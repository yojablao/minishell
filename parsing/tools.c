/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:50:24 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/27 18:15:09 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//  #include <errno.h>

char *f_substr(char const *s, unsigned int start, size_t len)
{
	char *new;
	char *src;
	size_t l;
	size_t i;

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
void add_env(t_env **head, char *key, char *value)
{
	t_env *new_env;
	t_env *tmp;

	new_env = (t_env *)master(sizeof(t_env), 1);
	new_env->key = f_strdup(key);
	new_env->value = f_strdup(value);
	new_env->valid = 1;
	new_env->next = NULL;

	if (*head == NULL)
		*head = new_env;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}
t_env *env_set(char **envi)
{
	t_env *env = NULL;

	int i = 0;
	int j;
	if (!envi)
		return NULL;
	while (envi[i])
	{
		j = 0;
		while (envi[i][j])
		{
			if (envi[i][j] == '=')
			{
				envi[i][j] = '\0';
				add_env(&env, &envi[i][0], &envi[i][j + 1]);
				envi[i][j] = '=';
				break;
			}
			j++;
		}
		i++;
	}
	return (env);
}
int count_words(char **words)
{
	int count = 0;
	while (words[count] != NULL)
		count++;
	return count;
}
bool pasabel(char *c)
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
char **correct_cmd(char **args, int *j)
{
	char **split_args;
	char **new_args;
	int original_count;
	int split_count;
	int i;
	int k;

	k = 0;
	i = 0;
	split_count = 0;
	original_count = *j;
	split_args = f_split(args[0], ' ', '\t');
	while (split_args[split_count] != NULL)
		split_count++;
	new_args = master((original_count + split_count + 1) * sizeof(char *), 1);
	while (k < split_count)
		new_args[i++] = split_args[k++];
	k = 1;
	while (k < original_count)
		new_args[i++] = args[k++];
	new_args[i] = NULL;
	*j = i;
	return new_args;
}

void ft_printf_a(t_list *a)
{
	t_list *tmp = a;
	while (tmp)
	{
		printf("{%s}\n", tmp->content);
		tmp = tmp->next;
	}
}

char *select_word(char *content, char *expanded, int status)
{
	if (status == -1 || status != 4)
		return expanded;
	else
		return f_strdup(content);
}
char **ft_joinlist(t_list **lst, t_environment **env, int status)
{
	int index;
	char **words;
	char *expanded;

	index = 0;
	words = master(sizeof(char *) * (ft_lstsize(*lst) + 1), 1);
	while (*lst && (*lst)->stat != 0)
	{
		expanded = ft_expand1((*lst)->content, (*env)->env, (*env)->lenv);
		if (expanded && *expanded)
		{
			words[index++] = select_word((*lst)->content, expanded, status);
			if ((*env)->lenv->flage)
				words = correct_cmd(words, &index);
		}
		status = (*lst)->stat;
		*lst = (*lst)->next;
	}
	if (*lst && (*lst)->stat == 0)
		*lst = (*lst)->next;

		
	words[index] = NULL;
	return (words);
}

void filehandler(t_exec_cmd **s)
{
	if ((*s)->infd == -1 ||  (*s)->outfd == -1)
		exit(EXIT_FAILURE);
	if ((*s)->infd != 0 && (*s)->infd != -1)
	{
		if (dup2((*s)->infd, STDIN_FILENO) == -1)
		{
			// perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
		close((*s)->infd);
	}
	if ((*s)->outfd != 1 && (*s)->outfd != -1)
	{
		if (dup2((*s)->outfd, 1) == -1)
		{
			// perror(strerror(errno));
			exit(EXIT_FAILURE);
		}
		close((*s)->outfd);
	}
}
void f(void *content)
{
	char *s;
	int i = 0;
	int j = 0;
	int single_q;
	int double_q;

	single_q = 0;
	double_q = 0;
	s = (char *)content;
	while (s[i])
	{
		if (s[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (s[i] == '"' && !single_q)
			double_q = !double_q;
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}
