/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:19:46 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/08 15:19:46 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (big[0] == '\0' || len == 0)
		return (NULL);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && i + j < len)
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char big[] = "aaabcabcd";
// 	char little[] = "a";
// 	printf("%s\n", ft_strnstr(big, little, 1));
// 	char big1[] = "je suis lily ";
// 	char little1[] = "lily";
// 	printf("%s\n", ft_strnstr(big1, little1, siz'\0'(big1)));
// 	return (0);
// }