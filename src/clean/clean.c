/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 21:23:08 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/26 21:23:08 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_clean(t_token *head, t_ast *ast, t_shell *shell, int status)
{
	if (head)
		ft_lstfree(head);
	if (ast)
		ft_free_ast(ast);
	shell->token = NULL;
	shell->ast = NULL;
	if (shell && shell->exit == true)
	{
		if (shell && shell->build_env)
		{
			ft_free_dba(shell->build_env);
			shell->build_env = NULL;
		}
		exit(shell->last_exit_code);
	}
	return (status);
}

void	ft_clean_at_exit(t_ast *ast, t_shell *shell)
{
	if (ast)
	{
		ft_free_ast(ast);
		ast = NULL;
	}
	if (shell && shell->build_env)
	{
		ft_free_dba(shell->build_env);
		shell->build_env = NULL;
	}
	rl_clear_history();
	if (shell && shell->exit == true)
		exit(shell->last_exit_code);
}

void	ft_clean_at_end_cmd(t_token *tokens, t_ast *ast)
{
	if (tokens)
	{
		ft_lstfree(tokens);
		tokens = NULL;
	}
	if (ast)
	{
		ft_free_ast(ast);
		ast = NULL;
	}
}

void	ft_clean_all_child(t_shell *shell, int nb)
{
	if (shell && shell->ast)
	{
		ft_free_ast(shell->ast);
		shell->ast = NULL;
	}
	if (shell && shell->token)
	{
		ft_lstfree(shell->token);
		shell->token = NULL;
	}
	if (shell && shell->build_env)
	{
		ft_free_dba(shell->build_env);
		shell->build_env = NULL;
	}
	if (shell && shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	rl_clear_history();
	exit(nb);
}
