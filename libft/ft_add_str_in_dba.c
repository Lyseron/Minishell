/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_in_db_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:55:49 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/13 20:55:49 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_add_str(int *j, char **new_arr, char *s)
{
	new_arr[*j] = ft_strdup(s);
	if (!new_arr[*j])
		return (ft_free_before_i(new_arr, *j), 1);
	(*j)++;
	return (0);
}

static int	ft_norm(char **arr, char **new_arr, int pos, char *s_to_add)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_dba_len(arr);
	while (i < len)
	{
		if (i == pos && ft_add_str(&j, new_arr, s_to_add) == 1)
			return (1);
		if (ft_add_str(&j, new_arr, arr[i]) == 1)
			return (1);
		i++;
	}
	if (pos == len && ft_add_str(&j, new_arr, s_to_add) == 1)
		return (1);
	new_arr[j] = NULL;
	return (0);
}

char	**ft_add_str_in_dba(char **arr, char *s_to_add, int pos)
{
	int		len_arr;
	int		len_s;
	char	**new_arr;

	if (!arr || !s_to_add)
		return (NULL);
	len_s = ft_strlen(s_to_add);
	len_arr = ft_dba_len(arr);
	if (len_s <= 0 || pos < 0 || pos > len_arr)
		return (NULL);
	new_arr = malloc(sizeof(char *) * (len_arr + 2));
	if (!new_arr)
		return (NULL);
	if (ft_norm(arr, new_arr, pos, s_to_add) == 1)
		return (NULL);
	ft_free_dba(arr);
	return (new_arr);
}
