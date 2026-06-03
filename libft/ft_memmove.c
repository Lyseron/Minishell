/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:25:33 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/07 20:25:33 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	back(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*sr;
	size_t				i;

	dst = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	i = n;
	while (i > 0)
	{
		i--;
		dst[i] = sr[i];
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*sr;
	size_t				i;

	dst = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	if (!dest && !src)
		return (0);
	if (dst == sr || n == 0)
		return (dest);
	if (dst > sr)
		back(dst, sr, n);
	else
	{
		i = 0;
		while (i < n)
		{
			dst[i] = sr[i];
			i++;
		}
	}
	return (dest);
}
