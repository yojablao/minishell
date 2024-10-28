/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:26:46 by yojablao          #+#    #+#             */
/*   Updated: 2024/10/28 04:05:19 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_option(char **word, int *i)
{
	int j;
	bool flage;

	flage = false;
	if (!word[*i])
		return false;
	while (word[++(*i)])
	{
		if (word[*i][0] == '-')
		{
			j = 0;
			while (word[*i][++j])
			{
				if (word[*i][j] == 'n')
					flage = true;
				else
				{
					flage = false;
					break;
				}
			}
		}
		else
			return (flage);
	}
	return (flage);
}
void print_echo(char **input, bool flage, int i)
{
	if(flage == false)
		i--;
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1])
			printf(" ");
		i++;
	}
	if (!flage)
		printf("\n");
}
void echo(char **input)
{
	int i = 0;
	bool option;

	if (!input || !*input)
	{
		get_exit(1, 0);
		return;
	}
	option = check_option(input, &i);
	printf("%d->>\n",i);
	if (!input[i] && option)
	{
		get_exit(1, 0);
		return;
	}
	print_echo(input, option, i);
	get_exit(0, 0);
}
