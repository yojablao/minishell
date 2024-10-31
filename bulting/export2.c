/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:22:05 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/31 14:29:44 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(char *command, int mybool)
{
	int	j;

	j = -1;
	if (!ft_isalpha(command[0]) && command[0] != '_')
		return (1);
	while (command[++j])
	{
		if (command[j] == '=' && mybool == 0)
			return (0);
		if (!ft_isalnum(command[j]) && command[j] != '_' && command[j] != '+')
			return (1);
		if (command[j] == '+' && command[j + 1] == '=')
			return (0);
		else if (command[j] == '+' && command[j + 1] != '=')
			return (1);
	}
	return (0);
}

void	print_error(char *error_msg, char *identifier, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("`: ", 2);
	ft_putstr_fd(error_msg, 2);
	get_exit(1, 0);
}

int	key_exists(char *str, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	add_or_update(t_environment **env, char *s)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
		{
			s[i] = '\0';
			key = f_strdup(s);
			value = f_strdup(&s[i + 2]);
			add_to_env(&(*env)->lenv, key, value, 1);
			return ;
		}
		else if (s[i] == '=')
		{
			s[i] = '\0';
			key = f_strdup(s);
			value = f_strdup(&s[i + 1]);
			add_to_env(&(*env)->lenv, key, value, 0);
			return ;
		}
		i++;
	}
}
