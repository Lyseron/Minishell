/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 02:30:55 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/01 02:30:55 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_env(char **env)
{
	int	i;

	if (!env)
		return (OK);
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (OK);
}
