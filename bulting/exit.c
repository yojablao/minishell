/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:43:59 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/29 05:36:12 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool check_is_number(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
bool multi_argiment(char **args)
{
	// int i;
	int exit_status;
	char *trim ;
	trim = f_strtrim(args[1]," ");
	// printf("%s\n",trim);
	if (!check_is_number(trim))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell : exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		// printf("%d\n", get_exit(0, 1));
		exit(255);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell : exit: too many arguments\n", 2);
		return (get_exit(1, 0),0);
	}
	exit_status = ft_atoi(trim) % 256;
	get_exit(exit_status, 0);
	ft_putstr_fd("exit\n", 2);
	exit(get_exit(0, 1));
}
void exit_builting(char **args, bool flage)
{
	if (!args[1])
	{
		if (flage)
			ft_putstr_fd("exit\n", 2);
		get_exit(0, 0);
		exit(0);
	}
	if (!multi_argiment(args))
		return;
}