/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jercleme <jercleme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:19:46 by jercleme          #+#    #+#             */
/*   Updated: 2026/04/01 01:19:46 by jercleme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_build_new_env(char **env, char *key, int len)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) != 0 || env[i][len] != '=')
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (ft_free_before_i(new_env, i), NULL);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	ft_builtin_unset(char ***env, char *key)
{
	char	**new_env;

	if (!key)
		return (OK);
	new_env = ft_build_new_env(*env, key, ft_strlen(key));
	if (!new_env)
		return (ERROR);
	ft_free_dba(*env);
	*env = new_env;
	return (OK);
}
