/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:47:10 by yojablao          #+#    #+#             */
/*   Updated: 2024/11/04 18:19:12 by yojablao         ###   ########.fr       */
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
	if (str[1] == NULL && (*env)->env)
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
	}
	(!flage) && (get_exit(0, 0));
	return (0);
}
