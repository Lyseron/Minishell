/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jercleme <jercleme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:19:46 by jercleme          #+#    #+#             */
/*   Updated: 2026/04/01 01:19:46 by jercleme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_replace(char **env, char *key, char *new_entry)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			env[i] = ft_strdup(new_entry);
			return (env);
		}
		i++;
	}
	return (env);
}

char	**ft_copy_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (ft_free_before_i(env, i), NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*ft_getenv(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	ft_env_with_smt(t_ast *ast, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
	{
		ast->args = ft_rm_str_in_dba(ast->args, 0);
		if (!ast->args || !ast->args[0])
			exit(127);
		ft_exec_cmd_child(ast, shell);
	}
	status = ft_wait_cmd(pid);
	if (status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	return (status);
}
