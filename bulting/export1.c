/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:47:10 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/28 09:07:33 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	find_target(char *str, char c);
void	export_print(char **tab)
{
	int	i;
	int	j;

	i = -1;
	while (tab[++i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		if (find_target(tab[i], '='))
		{
			while (tab[i][j])
			{
				if (tab[i][j] == '=')
				{
					printf("=\"%s\"", &tab[i][j + 1]);
					break ;
				}
				ft_putchar_fd(tab[i][j], 1);
				j++;
			}
			printf("\n");
		}
		else
			printf("%s\n", tab[i]);
	}
}
void	print_export(char **tab, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[j];
				tab[j] = tab[i];
				tab[i] = temp;
			}
			j++;
		}
		i++;
	}
	export_print(tab);
}

int	sizeenv(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

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

bool	find_target(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	add_key_env(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = master(sizeof(t_env), 1);
	if (!new_node)
		return ;
	new_node->key = f_strdup(key);
	new_node->value = f_strdup(value);
	new_node->valid = 0;
	new_node->next = NULL;
	if (*env == NULL)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	// printf("%s\n",tmp->next->value);
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
// void update_env(t_environment **top_env)
// {
// 	// free2d((*top_env)->env);
// }
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
int	validation(char **str, int i, t_environment **env)
{
	if (is_valid_identifier(str[i], 0) == 1)
		return (1);
	if (find_target(str[i], '='))
		add_or_update(env, str[i]);
	else
	{
		if (!key_exists(str[i], (*env)->lenv))
			add_key_env(&(*env)->lenv, str[i], NULL);
	}
	return (0);
}
int	export_builtin(char **str, t_environment **env)
{
	int		i;
	bool	flage;

	flage = false;
	if (!str)
		return (1);
	if (str[1] == NULL)
	{
		print_export((*env)->env, sizeenv((*env)->env));
		return (0);
	}
	i = 0;
	while (str[++i])
	{
		if (validation(str, i, env) == 1)
		{
			flage = true;
			print_error("not a valid identifier\n", str[i], str[0]);
			get_exit(1, 0);
		}
		(*env)->env = join_to_env((*env)->lenv);
		// update_env(env);
	}
	(!flage) && (get_exit(0, 0));
	return (0);
}
