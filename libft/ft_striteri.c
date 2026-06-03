/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:00:56 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/11 18:00:56 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	s_len;

	if (!s || !f)
		return ;
	i = 0;
	s_len = ft_strlen(s);
	while (i < s_len)
	{
		(*f)(i, &s[i]);
		i++;
	}
}
