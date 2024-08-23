/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:00:04 by hamrachi          #+#    #+#             */
/*   Updated: 2023/12/12 14:09:48 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_my_coun(int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		i += 1;
		nb *= -1;
	}
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*new;
	int			k;
	long int	s;

	if (n == 0)
		return (ft_strdup("0"));
	s = (long int)n;
	k = ft_my_coun(n);
	new = (char *)malloc(k + 1);
	if (!new)
		return (NULL);
	new[k] = '\0';
	if (s < 0)
	{
		new[0] = '-';
		s *= -1;
	}
	while (s > 0)
	{
		new[--k] = (s % 10) + 48;
		s /= 10;
	}
	return (new);
}
