/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:08:24 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/24 18:08:24 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_check(t_ast *ast, t_shell *shell)
{
	int	exit_code;

	if (!ast || !shell->build_env)
		return (ERROR);
	exit_code = ft_exec(ast, shell);
	return (exit_code);
}

int	ft_exec(t_ast *ast_node, t_shell *shell)
{
	if (!ast_node || !shell->build_env)
		return (ERROR);
	if (ft_sig_init(SIGINT, ft_handler_exec, 0) == ERROR)
		return (ERROR);
	if (ast_node->type == AST_CMD)
		return (ft_exec_cmd(ast_node, shell));
	else if (ast_node->type == AST_PIPE)
		return (ft_exec_pipe(ast_node, shell));
	else
		return (ERROR);
}

int	ft_exec_in_pipe(t_ast *ast_node, t_shell *shell)
{
	if (!ast_node || !shell->build_env)
		return (ERROR);
	if (ast_node->type == AST_CMD)
		return (ft_exec_cmd_pipe(ast_node, shell));
	else if (ast_node->type == AST_PIPE)
		return (ft_exec_pipe(ast_node, shell));
	else
		return (ERROR);
}

void	ft_exit_enotdir(t_ast *ast, t_shell *shell)
{
	ft_print_err_msg(ast->args[0], strerror(errno));
	ft_clean_all_child(shell, 126);
}
