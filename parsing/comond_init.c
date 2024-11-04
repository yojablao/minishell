/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comond_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:29:44 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/04 17:25:00 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		tmp1 = find_path_cmd(comond, path);
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
	int		i;
	char	**words;
	char	*expanded;

	i = 0;
	words = master(sizeof(char *) * (ft_lstsize(*lst) + 1), 1);
	while (*lst && (*lst)->stat != 0)
	{
		if (i >= 0 && empty_q((*lst)->content))
			words[i++] = f_strdup("\1");
		else
		{
			expanded = ft_expand1((*lst)->content, (*env)->env, (*env)->lenv);
			if ((expanded && *expanded) || status == 4)
			{
				words[i++] = valid_exp((*lst)->content, expanded, status);
				if ((*env)->lenv->flage)
					words = fix_cmd(words, &i, &(*env)->lenv);
			}
		}
		(1 && (status = (*lst)->stat), *lst = (*lst)->next);
	}
	init_lst_index(lst);
	words[i] = NULL;
	return (words);
}
