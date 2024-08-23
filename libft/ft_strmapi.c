/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:29:35 by hamrachi          #+#    #+#             */
/*   Updated: 2023/12/12 20:58:42 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*d;
	char			*new;
	unsigned int	i;
	unsigned int	len;

	if (!s || !f)
		return (NULL);
	d = (char *)s;
	len = ft_strlen(d);
	i = 0;
	new = (char *)malloc(len + 1);
	if (!new)
	{
		return (NULL);
	}
	while (i < len)
	{
		new[i] = f(i, d[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
