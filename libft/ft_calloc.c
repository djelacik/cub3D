/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:57:35 by djelacik          #+#    #+#             */
/*   Updated: 2024/05/07 13:21:39 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;
	size_t	total;

	if (count != 0 && size > 18446744073709551615ULL / count)
		return (NULL);
	total = count * size;
	buffer = malloc(total);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, total);
	return (buffer);
}
