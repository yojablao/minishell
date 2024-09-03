// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   syntax.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/20 01:04:07 by hamrachi          #+#    #+#             */
// /*   Updated: 2024/08/24 18:59:01 by hamrachi         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// size_t	skip_betw_quotes(char *str, size_t *i)
// {
// 	size_t cnt;

// 	cnt = 0;
// 	if (str[*i] == 34)
// 	{
// 		(*i)++;
// 		while (str[*i] != 34 && str[*i])
// 		{
// 			cnt += 1;
// 			(*i)++;
// 		}
// 	}
// 	if (str[*i] == 39)
// 	{
// 		(*i)++;
// 		while (str[*i] != 39 && str[*i])
// 		{
// 			cnt += 1;
// 			(*i)++;
// 		}
// 	}
// 	return (cnt);
// }

// int	ft_check_quotes(char *str)
// {
// 	t_quotes	qu;

// 	qu.i = 0;
// 	qu.q = 0;
// 	while (str[qu.i] != '\0')
// 	{
// 		if (str[qu.i] == 34 || str[qu.i] == 39)
// 		{
// 			qu.q += skip_betw_quotes(str, &qu.i);
// 			if (str[qu.i] == '\0')
// 				return(0);
// 		}
// 		qu.i++;
// 	}
// 	return (1);
// }

// size_t	ft_strlen_spaces(char *str)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 34 || str[i] == 39)
// 		{
// 			i += skip_betw_quotes(str, &i);
// 			i++;
// 		}
// 		if (str[i] == '|')
// 			j += 1;
// 		if (str[i] == '<' && str[i - 1] != '<' && str[i + 1] != '<')
// 			j += 1;
// 		if (str[i] == '>' && str[i - 1] != '>' && str[i + 1] != '>')
// 			j += 1;
// 		if (str[i] == '<' && str[i + 1] == '<')
// 			j += 1;
// 		if (str[i] == '>' && str[i + 1] == '>')
// 			j += 1;
// 		i++;
// 	}
// 	return (j);
// }

// void	add_spaces(char c, char *new, size_t *j, int v)
// {
// 	if (v == 0)
// 	{
// 		new[*j] = ' ';
// 		(*j)++;
// 		new[*j] = c;
// 		(*j)++;
// 		new[*j] = ' ';
// 		(*j)++;
// 	}
// 	else
// 	{
// 		new[*j] = ' ';
// 		(*j)++;
// 		new[*j] = c;
// 		(*j)++;
// 		new[*j] = c;
// 		(*j)++;
// 		new[*j] = ' ';
// 		(*j)++;
// 	}
// }

// size_t	ft_write_bet_quotes(char *str, char *new, size_t *i, size_t *j)
// {
// 	size_t c;

// 	c = 0;
// 	if (str[*i] == 34)
// 	{
// 		new[*j] = str[*i];
// 		(*i)++;
// 		(*j)++;
// 		while (str[*i])
// 		{
// 			if (str[*i] == 34)
// 			{
// 				new[*j] = str[*i];
// 				break;
// 			}
// 			c++;
// 			new[*j] = str[*i];
// 			(*i)++;
// 			(*j)++;
// 		}
// 	}
// 	return(c);
// }

// char	*ft_correct_line(char *str)
// {
// 	char	*new;
// 	t_correc	ind;

// 	new = ft_my_malloc((ft_strlen(str) + (ft_strlen_spaces(str)) * 2));
// 	printf("allocate -> %lu\n",(ft_strlen(str) + (ft_strlen_spaces(str) * 2)));
// 	ind.j = 0;
// 	ind.i = 0;
// 	while (str[ind.i])
// 	{
// 		if (str[ind.i] == 39 || str[ind.i] == 34)
// 		{
// 			printf("i = %zu\n", ind.i);
// 			ind.i += ft_write_bet_quotes(str, new, &ind.i, &ind.j);
// 			printf("i = %zu\n", ind.i);
// 		}
// 		if (((str[ind.i] == '<' && str[ind.i + 1] == '<')
// 				|| (str[ind.i] == '>' && str[ind.i + 1] == '>')))
// 			{
// 				add_spaces(str[ind.i], new, &ind.j, 1);
// 				ind.i++;
// 			}
// 		else if ((str[ind.i] == '|' || (str[ind.i] == '<' && str[ind.i + 1] != '<')
// 				|| (str[ind.i] == '>' && str[ind.i + 1] != '>')))
// 				add_spaces(str[ind.i], new, &ind.j, 0);
// 		else
// 				new[ind.j++] = str[ind.i];
// 		ind.i++;
// 	}
// 	return (new);
// }

// int	ft_skip_spaces(char *str, int c)
// {
// 	while (str)
// 	{
// 		if (*str != ' ')
// 			break;
// 		str++;
// 	}
// 	if ((*str == '|' || *str == '>' || *str == '<') && c == 0)
// 		return (0);
// 	if ((*str == '|' || (*str == '<' && *(str + 1) == '<')) && c == 2)
// 		return (0);
// 	if (*str == '\0' && c == 1)
// 		return (0);
// 	return (1);
// }

// int	ft_position_para(char	*str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] == ' ')
// 		i++;
// 	//if (str[i] ==  '|' || str[i] == '<' || str[i] == '>')
// 		//return (0);
// 	while(str[i])
// 	{
// 		if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && 
// 			ft_skip_spaces(&str[i + 1],1) == 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	ft_rank_para(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '|' && ft_skip_spaces(&str[i + 1], 2) == 0)
// 			return (0);
// 		if (str[i] == '<' && ft_skip_spaces(&str[i + 1], 0) == 0)
// 			return (0);
// 		if (str[i] == '>' && ft_skip_spaces(&str[i + 1], 0) == 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
// int	syntax_ok(char *str)
// {
// 	if (!ft_check_quotes(str) || !ft_position_para(str) || !ft_rank_para(str))
// 		return (0);
// 	printf("%s\n", ft_correct_line(str));
// 	//printf("%zu\n", ft_strlen_spaces(str));
// 	return (1);
// }
// // just correct  line with space and  respect no space if tokens inside " | << >> < >";
// /*
// char l = s[i++];
// while(s[i])
// 	if (s[i++] == l)
// 		break;
// */
// // char **str 