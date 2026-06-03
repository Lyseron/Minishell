/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:50:09 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/08 11:50:09 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	c1;

	c1 = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;
	if (c1 == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		i--;
		if ((unsigned char)s[i] == c1)
			return ((char *)&s[i]);
	}
	return (NULL);
}
