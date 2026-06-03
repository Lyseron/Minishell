/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:20:09 by lyaberge          #+#    #+#             */
/*   Updated: 2025/11/11 19:20:09 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(long n)
{
	int	len;

	if (n == 0)
		return (1);
	if (n < 0)
		n = n * -1;
	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	malloc_len(long n)
{
	int	len;

	len = n_len(n);
	if (n < 0)
	{
		len = n_len(n) + 1;
		return (len);
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*tab;
	int		len;
	int		i;

	nb = (long)n;
	len = malloc_len(nb);
	tab = malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	tab[len] = '\0';
	if (nb < 0)
	{
		tab[0] = '-';
		nb = nb * -1;
	}
	if (nb == 0)
		tab[0] = '0';
	i = len - 1;
	while (nb > 0)
	{
		tab[i--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (tab);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(-1));
// 	return (0);
// }