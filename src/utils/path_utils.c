/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:19:22 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/26 12:19:22 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parsing of the PATH in the environement
// -> return a line without the "PATH=" with all the paths to be split later
char	*ft_extract_p(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

// check if the string contain a slash
int	ft_contain_slash(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

// check the access for the exit 
// -> 0 = succes(exec + exist)
// -> 127 = cmd does not exist
// -> 126 = cmd exist but is not executable
int	ft_access_return(char *path)
{
	if (ft_is_a_directory(path))
		return (127);
	if (access(path, F_OK) != 0)
		return (127);
	if (access(path, X_OK) != 0)
		return (126);
	return (0);
}

// check if the string is a file
// -> 1 = yes
// -> 0 = nope
int	ft_is_a_directory(char *cmd)
{
	struct stat	st;

	if (!cmd)
		return (0);
	if (stat(cmd, &st) == -1)
		return (0);
	if (S_ISDIR(st.st_mode) == 1)
		return (1);
	return (0);
}

// for the right return status if no right path is found
// -> 127 = cmd does not exist
// -> 126 = cmd exist but is not executable
char	*ft_return_status(int *found, int *status)
{
	if (*found == 1)
		return (*status = 126, NULL);
	else
		return (*status = 127, NULL);
}
