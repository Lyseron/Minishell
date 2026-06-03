/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 19:22:48 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/09 20:08:04 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	tab = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tab[i + j] = s2[j];
		j++;
	}
	tab[i + j] = '\0';
	return (tab);
}
