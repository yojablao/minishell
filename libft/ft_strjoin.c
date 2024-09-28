/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 23:03:10 by hamrachi          #+#    #+#             */
/*   Updated: 2024/09/28 12:29:23 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
	{
	char		*r;
	size_t		ls1;
	size_t		ls2;
	size_t		t;
	size_t		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 && s2)
		return(ft_strdup(s2));
	i = 0;
	ls1 = ft_strlen(s1) + 1;
	ls2 = ft_strlen(s2);
	if (ls1 == 0 && ls2 == 0)
	{
		return (ft_strdup(""));
	}
	r = (char *)malloc((ls1 + ls2) * sizeof(char));
	if (!r)
	{
		return (NULL);
	}
	t = ft_strlcpy(r, s1, (ls1));
	t = ft_strlcat(r, s2, (ls1 + ls2));
	return (r);
}
