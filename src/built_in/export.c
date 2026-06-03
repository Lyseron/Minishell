/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jercleme <jercleme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:19:46 by jercleme          #+#    #+#             */
/*   Updated: 2026/04/01 01:19:46 by jercleme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_export(char **env)
{
	int		i;
	char	*equal;

	i = 0;
	while (env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (equal)
		{
			ft_putstr_fd("export ", 1);
			write(1, env[i], equal - env[i]);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(equal + 1, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd("export ", 1);
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}

static int	ft_is_valid_key(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	**ft_env_add(char **env, char *arg)
{
	char	**new_env;
	int		size;
	int		i;

	size = ft_env_size(env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (ft_free_before_i(new_env, i), NULL);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	if (!new_env[i])
		return (ft_free_before_i(new_env, i), NULL);
	new_env[i + 1] = NULL;
	ft_free_dba(env);
	return (new_env);
}

static int	ft_key_exists(char **env, char *arg)
{
	int		i;
	int		len;
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (0);
	len = equal - arg;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0 && env[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_builtin_export(char ***env, char *arg)
{
	char	*key;
	char	*equal;
	int		len;

	if (!arg)
		return (ft_print_export(*env), 0);
	if (!ft_is_valid_key(arg))
	{
		ft_print_err_msg_export("export", "not a valid identifier", arg);
		return (ERROR);
	}
	if (ft_key_exists(*env, arg))
	{
		equal = ft_strchr(arg, '=');
		len = equal - arg;
		key = ft_substr(arg, 0, len);
		*env = ft_env_replace(*env, key, arg);
		free(key);
	}
	else
		*env = ft_env_add(*env, arg);
	return (OK);
}
