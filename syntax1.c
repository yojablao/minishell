/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:46:07 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/03 18:28:55 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_betw_quotes(char *str, size_t *i)
{
    if (str[*i] == 34)
    {
        (*i)++;
        while (str[*i] != 34 && str[*i] != '\0')
            (*i)++;
    }
    else if(str[*i] == 39)
    {
        (*i)++;
        while (str[*i] != 39 && str[*i] != '\0')
            (*i)++;
    }
}

size_t  ft_count_operators(char *str)
{
   	t_num_operat s;
	size_t	i;
	size_t res;

	s.pipe = 0;
	s.her = 0;
	s.inp = 0;
	s.out = 0;
	s.app = 0;
	i = 0;
    while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			skip_betw_quotes(str, &i);
		if (str[i] == '|')
			s.pipe += 1;
		if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] != '<')
			s.inp += 1;
		if (str[i - 1] != '>' && str[i] == '>'&& str[i + 1] != '>')
			s.out += 1;
		if (str[i - 1] != '>' && str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
			s.app += 1;
		if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			s.her += 1;
		i++;	
	}
	// printf("pipe = %zu\n ",s.pipe);
	// printf("inp = %zu\n ",s.inp);
	// printf("out = %zu\n ",s.out);
	// printf("app = %zu\n ",s.app);
	// printf("her = %zu\n ",s.her);
	res = (s.pipe + s.app + s.her + s.inp + s.out) * 2;
	printf("res == %zu\n",res);
	return (res);
}

char    *ft_handel_spaces_allocation(char *str)
{
    char *new;
	size_t len1;
    size_t len2;

    len2 = ft_count_operators(str);
	len1  = ft_strlen(str) + len2;
	printf("len1 %zu\n",len1);
	new = ft_my_malloc(len1 + 1);
	return(new);
}

int	ft_check_quotes(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			skip_betw_quotes(str, &i);
			if (str[i] == '\0')
				return(0);
		}
		i++;
	}
	return (1);
}
void	ft_write_bet_quotes(char *str, char *new, int *i, int *j)
{
	char l;

	l = str[*i];
	new[(*j)++] = str[(*i)++];

	while (str[*i])
	{
		if (str[*i] == l)
			break;
		new[(*j)++] = str[(*i)++];
	}
	new[(*j)++] = str[(*i)];
}

void	add_spaces(char c, char *new, int *j, int v)
{
	if (v == 0)
	{
		new[(*j)++] = ' ';
		new[(*j)++] = c;
		new[(*j)++] = ' ';
	}
	else
	{
		new[(*j)++] = ' ';
		new[(*j)++] = c;
		new[(*j)++] = c;
		new[(*j)++] = ' ';
	}
}

void	ft_add_spaces(char *str, char *new)
{
	int i = 0;
	int j = 0;

	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			ft_write_bet_quotes(str, new, &i, &j);
		else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			add_spaces(str[i++], new, &j, 1);
		else if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<') || (str[i] == '>' && str[i + 1] != '>'))
			add_spaces(str[i], new, &j, 0);
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
}
int	ft_check_her(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (0);
		if (str[i] == '<' && str[i + 1] == '<' && 
			str[i + 2] == '<' && str[i + 3] == '<')
			return (0);
		i++;
	}
	return(1);
}

int syntax(char *str)
{
    char *new;
	t_list *a;

	a = NULL;
	if (!ft_check_quotes(str) || !ft_check_her(str))     
	{
		free(str);
		return (0);
	}
    new = ft_handel_spaces_allocation(str);
	ft_add_spaces(str,new);
	ft_full_list(&a, new);
	//ft_check_grammer(a); (loop nodes for check condition of grammer)
	ft_free_stack(a);
	free(new);
	free(str);
	return (1);
}
