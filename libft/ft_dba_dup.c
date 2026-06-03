/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_arr_dup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:37:24 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/13 20:37:24 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dba_dup(char **arr)
{
	int		i;
	char	**dup_arr;
	int		len;

	if (!arr)
		return (NULL);
	len = ft_dba_len(arr);
	if (len == 0)
		return (NULL);
	dup_arr = malloc(sizeof(char *) * (len + 1));
	if (!dup_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup_arr[i] = ft_strdup(arr[i]);
		if (!dup_arr[i])
			return (ft_free_before_i(dup_arr, i), NULL);
		i++;
	}
	dup_arr[i] = NULL;
	return (dup_arr);
}
