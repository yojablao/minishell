/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:40:27 by hamrachi          #+#    #+#             */
/*   Updated: 2023/12/12 13:16:05 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*m;
	size_t			i;

	m = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		m[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
