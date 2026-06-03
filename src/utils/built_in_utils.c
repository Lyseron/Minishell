/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:57:13 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/01 01:57:13 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else
		return (OK);
}

int	ft_exec_built(t_ast *ast_node, char ***env, t_shell *shell, t_close *c)
{
	if (!ast_node || !ast_node->args || !ast_node->args[0])
		return (ERROR);
	if (ft_strcmp(ast_node->args[0], "pwd") == 0)
		return (ft_builtin_pwd(shell));
	else if (ft_strcmp(ast_node->args[0], "echo") == 0)
		return (ft_builtin_echo(ast_node->args, shell));
	else if (ft_strcmp(ast_node->args[0], "cd") == 0)
		return (ft_builtin_cd(env, ast_node->args));
	else if (ft_strcmp(ast_node->args[0], "export") == 0)
		return (ft_for_export(ast_node, env));
	else if (ft_strcmp(ast_node->args[0], "unset") == 0)
		return (ft_for_unset(ast_node, env));
	else if (ft_strcmp(ast_node->args[0], "exit") == 0)
		return (ft_builtin_exit(ast_node->args, shell, c));
	else if (ft_strcmp(ast_node->args[0], "env") == 0)
		return (ft_builtin_env(*env));
	return (OK);
}

int	ft_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_init_atoi(t_atoi *a)
{
	a->i = 0;
	a->result = 0;
	a->sign = 1;
	a->overflow = 0;
	a->nb = 0;
}
