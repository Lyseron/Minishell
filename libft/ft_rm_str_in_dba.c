/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_str_in_db_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:55:20 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/13 20:55:20 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_norm(int pos, char **new_arr, char **arr, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (i == pos)
			i++;
		else
		{
			new_arr[j] = ft_strdup(arr[i]);
			if (!new_arr[j])
				return (ft_free_before_i(new_arr, j), 1);
			i++;
			j++;
		}
	}
	new_arr[j] = NULL;
	return (0);
}

char	**ft_rm_str_in_dba(char **arr, int pos)
{
	int		len;
	char	**new_arr;

	if (!arr)
		return (NULL);
	len = ft_dba_len(arr);
	if (len == 0 || pos >= len || pos < 0)
		return (NULL);
	new_arr = malloc(sizeof(char *) * len);
	if (!new_arr)
		return (NULL);
	if (ft_norm(pos, new_arr, arr, len) == 1)
		return (NULL);
	ft_free_dba(arr);
	return (new_arr);
}
