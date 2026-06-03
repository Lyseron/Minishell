/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expans_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:46:30 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/09 08:46:30 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_ast_args(t_ast *ast, t_shell *shell);
static int	ft_handle_all_files(t_ast *ast, t_shell *shell);
static int	ft_handle_file(t_ast *ast, t_shell *shell);

int	ft_handle_all(t_ast *ast, t_shell *shell)
{
	if (ft_handle_ast_args(ast, shell) == ERROR)
		return (ERROR);
	if (ft_handle_all_files(ast, shell) == ERROR)
		return (ERROR);
	return (OK);
}

static int	ft_handle_all_files(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (OK);
	if (ft_handle_file(ast, shell) == ERROR)
		return (ERROR);
	if (ft_handle_all_files(ast->left, shell) == ERROR)
		return (ERROR);
	if (ft_handle_all_files(ast->right, shell) == ERROR)
		return (ERROR);
	return (OK);
}

static int	ft_handle_file(t_ast *ast, t_shell *shell)
{
	char	*tmp;
	char	*file;
	t_redir	*redir;

	if (!ast)
		return (OK);
	redir = ast->redirs;
	while (redir)
	{
		if (redir->file)
		{
			tmp = redir->file;
			file = ft_expand(redir->file, shell);
			if (!file)
				return (ERROR);
			redir->file = file;
			free(tmp);
		}
		redir = redir->next;
	}
	return (OK);
}

static int	ft_handle_ast_args(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (OK);
	if (ast->type == AST_CMD)
		return (ft_handle_args(ast, shell));
	if (ast->type == AST_PIPE)
	{
		if (ft_handle_ast_args(ast->left, shell) == ERROR)
			return (ERROR);
		if (ft_handle_ast_args(ast->right, shell) == ERROR)
			return (ERROR);
	}
	return (OK);
}
