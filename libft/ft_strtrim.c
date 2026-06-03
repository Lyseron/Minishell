/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:44 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/10 15:14:44 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contain(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	int		start;
	int		end;
	char	*tab;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	start = 0;
	while (contain(s1[start], set) == 1)
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (contain(s1[end], set) == 1)
		end--;
	tab = malloc(sizeof(char) * ((end - start + 1) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (start <= end)
		tab[i++] = s1[start++];
	tab[i] = '\0';
	return (tab);
}
