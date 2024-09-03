/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/02 20:07:06 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	leaks()
{
	system("leaks minishell");
}
int main(int ac, char **av, char **env)
{
	char    *input;

	(void)ac;
	(void)av;
	(void)env;

	atexit(leaks);
	while (1)
	{ 
		input = readline("myshell> ");
		
		if (input ==  NULL || !*input)
		{
			free(input);
			printf("empty\n");
			return (1);
		}
		else
		{
			add_history(input);
			if(!syntax(input))
				printf("syntax error\n");
		}
	}
	return (0);
}