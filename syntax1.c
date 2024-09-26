/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:46:07 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/26 06:22:23 by yojablao         ###   ########.fr       */
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
char	*skip_betw_quotes2(char *str)
{
	if (*str == 34)
    {
        str++;
        while (*str != 34 && *str != '\0')
        	str++;
    }
    else if (*str == 39)
    {
        str++;
        while (*str != 39 && *str != '\0')
            str++;
    }
	return(str);
}

// size_t  ft_count_operators(char *str)
// {
//    	t_num_operat s;
// 	size_t	i;
// 	size_t res;

// 	s.pipe = 0;
// 	s.her = 0;
// 	s.inp = 0;
// 	s.out = 0;
// 	s.app = 0;
// 	i = 0;
//     while (str[i])
// 	{
// 		if (str[i] == 34 || str[i] == 39)
// 			skip_betw_quotes(str, &i);
// 		if (str[i] == '|')
// 			s.pipe += 1;
// 		if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] != '<')
// 			s.inp += 1;
// 		if (str[i - 1] != '>' && str[i] == '>'&& str[i + 1] != '>')
// 			s.out += 1;
// 		if (str[i - 1] != '>' && str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
// 			s.app += 1;
// 		if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
// 			s.her += 1;
// 		i++;	
// 	}
// 	res = (s.pipe + s.app + s.her + s.inp + s.out) * 2;
// 	printf("res == %zu\n",res);
// 	return (res);
// }
size_t  ft_count_operators(char *str)
{
   	t_num_operat s;
	size_t	i;
	size_t  res;

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
		
		// Ensure that i > 0 before accessing str[i-1]
		if (i > 0 && str[i - 1] != '<' && str[i] == '<' && str[i + 1] != '<')
			s.inp += 1;
		if (i > 0 && str[i - 1] != '>' && str[i] == '>' && str[i + 1] != '>')
			s.out += 1;
		if (i > 0 && str[i - 1] != '>' && str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
			s.app += 1;
		if (i > 0 && str[i - 1] != '<' && str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			s.her += 1;
		i++;	
	}
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
	//printf("len1 %zu\n",len1);
	new = ft_my_malloc(len1 + 1);
	return(new);
}

int	ft_check_quotes(char *str)
{
	size_t i;

	i = 0;
	while (str && str[i] != '\0')
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
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			skip_betw_quotes(str, &i);
		if(str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			return (0);
		if (str[i] == '<' && str[i + 1] == '<' && 
			str[i + 2] == '<')
			return (0);
		i++;
	}
	return(1);
}

int syntax(char *str,t_top **cmd)
{
    char *new;
	// t_list *a;
	// t_list *b;

	(*cmd)->a = NULL;
	// b = NULL;
	if (!ft_check_quotes(str) || !ft_check_her(str))
	{
		free(str);
		return (0);
	}
    new = ft_handel_spaces_allocation(str);
	ft_add_spaces(str, new);
	ft_full_list(&(*cmd)->a, new, 32);
	if (ft_check_grammer((*cmd)->a) == 0)
	{
		ft_free((*cmd)->a, str, new);
		return(0);
	}
	// (*cmd)->a = a;
	// ft_full_list(&b, new, 124);
	// ft_free(a, str, new);
	// ft_free_stack(b);
	return (1);
}
/*
split ("|");0 done;
char **allcmd == echo $DFdf > $USER 
char **cmd = echo \0
char **red = > file > hamrachi
*/