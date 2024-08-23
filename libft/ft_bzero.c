/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:18:58 by hamrachi          #+#    #+#             */
/*   Updated: 2023/12/01 17:58:20 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*m;
	size_t			i;

	i = 0;
	m = (unsigned char *)s;
	while (n > 0)
	{
		m[i] = 0;
		i++;
		n--;
	}
	return (s);
}
