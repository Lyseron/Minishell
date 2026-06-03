/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:29:13 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/11 17:29:13 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tab;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	tab = malloc(sizeof(char) * (s_len + 1));
	if (!tab)
		return (NULL);
	while (i < s_len)
	{
		tab[i] = (*f)(i, s[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

// char to_upper(unsigned int i, char c)
// {
// 	(void)i;
// 	if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	return (c);
// }

// int	main(void)
// {
// 	char s1[] = "lily";
// 	char *result = ft_strmapi(s1, to_upper);
// 	printf("%s\n", s1);
// 	printf("%s\n", result);
// 	return (0);
// }