/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamrachi <hamrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:23:50 by hamrachi          #+#    #+#             */
/*   Updated: 2023/12/12 16:54:51 by hamrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size > sizeof(size))
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero (str, (count * size));
	return (str);
}
