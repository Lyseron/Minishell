/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:41:37 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/07 19:41:37 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sr;
	size_t			i;

	if (!dest && !src)
		return (0);
	dst = (unsigned char *)dest;
	sr = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst[i] = sr[i];
		i++;
	}
	return (dest);
}
