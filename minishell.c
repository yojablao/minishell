/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 00:56:39 by hamrachi          #+#    #+#             */
/*   Updated: 2024/08/23 00:27:02 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int main(int ac, char **av, char **env)
{
	char    *input;

	(void)ac;
	(void)av;
	(void)env;

	
	while (1)
	{ 
		input = readline("myshell> ");
		if (input ==  NULL || !*input)
		{
			free(input);
			printf("empty\n");
		}
		else
		{
			if(!syntax_ok(input))
				printf("syntax error\n");
		}
	}
	return (0);
}