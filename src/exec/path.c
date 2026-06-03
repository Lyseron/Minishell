/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:11:34 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/26 12:11:34 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_path(char *split_path, char *possible_path, char *cmd);
char	*ft_return_if_contain_slash(char *cmd, int *status);
char	*ft_p_path(char *split_path, char *cmd, int *status, int *found);

// find the right path to send to execve depanding on the command
// and the status for the right exit in ft_for_cmd
char	*ft_test_path(char *path, char *cmd, int *status)
{
	int		i;
	char	**split_path;
	char	*possible_path;
	int		found;

	if (!cmd || cmd[0] == '\0')
		return (*status = 127, NULL);
	if (ft_contain_slash(cmd))
		return (ft_return_if_contain_slash(cmd, status));
	if (!path)
		return (*status = 127, NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (*status = 1, NULL);
	i = 0;
	found = 0;
	possible_path = NULL;
	while (split_path[i] && possible_path == NULL)
		possible_path = ft_p_path(split_path[i++], cmd, status, &found);
	if (possible_path)
		return (ft_free_dba(split_path), possible_path);
	ft_free_dba(split_path);
	return (ft_return_status(&found, status));
}

// take a path and create a string with a slash + the cmd 
// to be tester for access
void	ft_find_path(char *split_path, char *possible_path, char *cmd)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (split_path[k])
	{
		possible_path[j] = split_path[k];
		j++;
		k++;
	}
	possible_path[j] = '/';
	j++;
	k = 0;
	while (cmd[k])
	{
		possible_path[j] = cmd[k];
		j++;
		k++;
	}
	possible_path[j] = '\0';
}

// if cmd is already a path with a / return that path 
// if invalid path return a status to be handle later 
char	*ft_return_if_contain_slash(char *cmd, int *status)
{
	if (access(cmd, F_OK) != 0)
		return (*status = 127, NULL);
	else if (ft_is_a_directory(cmd) == 1)
		return (*status = 126, NULL);
	else if (access(cmd, X_OK) != 0)
		return (*status = 126, NULL);
	else
		return (*status = 0, ft_strdup(cmd));
}

// path = possible_path
// test different possible path to find the right one for the cmd
char	*ft_p_path(char *split_path, char *cmd, int *status, int *found)
{
	char	*path;
	int		error;

	path = malloc(sizeof(char) * (ft_strlen(split_path) + ft_strlen(cmd) + 2));
	if (!path)
		return (*status = 1, NULL);
	ft_find_path(split_path, path, cmd);
	error = ft_access_return(path);
	if (error == 0)
		return (*status = 0, path);
	else if (error == 126)
		*found = 1;
	free(path);
	return (NULL);
}
