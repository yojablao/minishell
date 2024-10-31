/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comond_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:29:44 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 11:14:21 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valide_comond(char *comond)
{
	if (ft_strchr(comond, '/'))
	{
		if (comond[ft_strlen(comond) - 1] == '/')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(comond, 2);
			ft_putstr_fd(": is a directory\n", 2);
			get_exit(126, 0);
			return (-1);
		}
		else
		{
			if (access(comond, X_OK))
				ft_putstr_fd(": No such file or directory\n", 2);
			return (0);
		}
	}
	return (1);
}

char	*find_comond(char *comond, t_env **env)
{
	char	*path;
	char	*tmp1;

	if (!comond)
		return (NULL);
	if (is_valide_comond(comond) == 0)
		return (comond);
	else if (is_valide_comond(comond) == -1)
		return (NULL);
	path = extract_value((*env), "PATH");
	if (path)
	{
		tmp1 = find_pexec(comond, path);
		if (tmp1 == NULL)
		{
			comnond_err(comond, *env);
			get_exit(127, 0);
			return (NULL);
		}
		else
			return (tmp1);
	}
	else
		return (comond);
	return (NULL);
}

void	init_lst_index(t_list **lst)
{
	if (*lst && (*lst)->stat == 0)
		*lst = (*lst)->next;
}

char	**ft_joinlist(t_list **lst, t_environment **env, int status)
{
	int		index;
	char	**words;
	char	*expanded;

	index = 0;
	words = master(sizeof(char *) * (ft_lstsize(*lst) + 1), 1);
	while (*lst && (*lst)->stat != 0)
	{
		if (index > 0 && empty_Q((*lst)->content))
			words[index++] = f_strdup("\0");
		else
		{
			expanded = ft_expand1((*lst)->content, (*env)->env, (*env)->lenv);
			if ((expanded && *expanded) || status == 4)
			{
				words[index++] = select_word((*lst)->content, expanded, status);
				if ((*env)->lenv->flage)
					words = correct_cmd(words, &index);
			}
		}
		(1 && (status = (*lst)->stat), *lst = (*lst)->next);
	}
	init_lst_index(lst);
	words[index] = NULL;
	return (words);
}
