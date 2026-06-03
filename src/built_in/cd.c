/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jercleme <jercleme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:19:46 by jercleme          #+#    #+#             */
/*   Updated: 2026/04/01 01:19:46 by jercleme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_path(char **env, char *arg)
{
	if (!arg || ft_strncmp(arg, "~", 1) == 0)
		return (ft_getenv(env, "HOME"));
	return (arg);
}

static int	ft_update_pwd(char ***env)
{
	char	buffer[4096];
	char	*new_pwd;

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (ft_print_err_msg("cd", strerror(errno)), 1);
	new_pwd = ft_strjoin("PWD=", buffer);
	if (!new_pwd)
		return (1);
	*env = ft_env_replace(*env, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

// changer pour msg_error
int	ft_builtin_cd(char ***env, char **arg)
{
	char	*path;

	if (arg[1] && arg[2])
		return (ft_print_err_msg("cd", "too many arguments"), ERROR);
	path = ft_get_path(*env, arg[1]);
	if (!path)
		return (ft_print_err_msg("cd", "HOME not set"), ERROR);
	if (chdir(path) == -1)
		return (ft_print_err_msg_spe("cd", strerror(errno), arg[1]), 1);
	return (ft_update_pwd(env));
}
