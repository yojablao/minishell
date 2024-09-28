/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:32:50 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/28 10:14:10 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n)
	{
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	if(str1[i] == '\0' && str1[i] != '\0')
		return (str1[i]);
	if(str1[i] == '\0' && str1[i] != '\0')
		return (str1[i]);
		
		
	return (str1[i] - str2[i]);
}
