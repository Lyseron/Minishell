/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:45:32 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/08 17:45:32 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tab;
	size_t			size_all;
	size_t			size_max;

	size_max = -1;
	if (size != 0 && count > size_max / size)
		return (NULL);
	size_all = size * count;
	tab = malloc(size_all);
	if (!tab)
		return (NULL);
	ft_bzero(tab, size_all);
	return (tab);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *lily = ft_calloc(INT_MIN, INT_MIN);
// 	if (!lily)
// 		printf("erreur malloc");
// 	else 
// 		free(lily);
// 	printf("%s\n", lily);
// 	int *tab = ft_calloc(5, siz'\0'(int));
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		printf("%d", tab[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	int *tab1 = calloc(5, siz'\0'(int));
// 	i = 0;
// 	while (i < 5)
// 	{
// 		printf("%d", tab1[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	char *str = ft_calloc(10, siz'\0'(char));
// 	printf("%s\n", str);
// 	char *str1 = calloc(10, siz'\0'(char));
// 	printf("%s\n", str1);
// 	return (0);
// }