/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jercleme <jercleme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:19:46 by jercleme          #+#    #+#             */
/*   Updated: 2026/04/01 01:19:46 by jercleme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_for_export(t_ast *ast_node, char ***env)
{
	int	i;
	int	status;
	int	status_real;

	i = 1;
	status_real = OK;
	if (!ast_node->args[1])
		return (ft_builtin_export(env, ast_node->args[1]));
	while (ast_node->args[i])
	{
		status = ft_builtin_export(env, ast_node->args[i]);
		if (status == ERROR)
			status_real = ERROR;
		i++;
	}
	return (status_real);
}

int	ft_for_unset(t_ast *ast_node, char ***env)
{
	int	i;
	int	status;
	int	status_real;

	i = 1;
	status_real = OK;
	while (ast_node->args[i])
	{
		status = ft_builtin_unset(env, ast_node->args[i]);
		if (status == ERROR)
			status_real = ERROR;
		i++;
	}
	return (status_real);
}
