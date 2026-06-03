/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:09:34 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/26 12:09:34 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lef(t_ast *left, int *std_in, int *std_out, t_shell *shell);
void	ft_rig(t_ast *right, int *std_in, int *std_out, t_shell *shell);

// handle the creation of both child for the pipe comand
// and wait for them to finish 
int	ft_exec_pipe(t_ast *ast_node, t_shell *shell)
{
	pid_t	pid_in;
	pid_t	pid_out;
	int		std_in;
	int		std_out;
	int		status;

	if (ft_create_pipe(&std_in, &std_out) == 1)
		return (ft_print_err_msg("pipe", strerror(errno)), 1);
	pid_in = fork();
	if (pid_in == -1)
		return (ft_close_fd(&std_in, &std_out, "pid_in"));
	else if (pid_in == 0)
		ft_lef(ast_node->left, &std_in, &std_out, shell);
	pid_out = fork();
	if (pid_out == -1)
		return (ft_close_fd(&std_in, &std_out, "pid_out"));
	else if (pid_out == 0)
		ft_rig(ast_node->right, &std_in, &std_out, shell);
	close(std_in);
	close(std_out);
	status = ft_wait(pid_in, pid_out);
	if (status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	return (status);
}

void	ft_lef(t_ast *left, int *std_in, int *std_out, t_shell *shell)
{
	int	status;

	if (!left)
	{
		status = ft_close_fd(std_in, std_out, "left");
		ft_clean_all_child(shell, status);
	}
	if (ft_sig_init(SIGINT, ft_handler_heredoc_child, 0) == ERROR)
	{
		status = ft_close_fd(std_in, std_out, "sigaction");
		ft_clean_all_child(shell, status);
	}
	shell->in_pipe = true;
	if (dup2(*std_out, 1) == -1)
	{
		status = ft_close_fd(std_in, std_out, "dup2");
		ft_clean_all_child(shell, status);
	}
	close(*std_in);
	close(*std_out);
	if (left->type == AST_CMD)
		status = ft_exec_cmd_pipe(left, shell);
	else
		status = ft_exec_in_pipe(left, shell);
	ft_clean_all_child(shell, status);
}

void	ft_rig(t_ast *right, int *std_in, int *std_out, t_shell *shell)
{
	int	status;

	if (!right)
	{
		status = ft_close_fd(std_in, std_out, "right");
		ft_clean_all_child(shell, status);
	}
	if (ft_sig_init(SIGINT, ft_handler_heredoc_child, 0) == ERROR)
	{
		status = ft_close_fd(std_in, std_out, "sigaction");
		ft_clean_all_child(shell, status);
	}
	shell->in_pipe = true;
	if (dup2(*std_in, 0) == -1)
	{
		status = ft_close_fd(std_in, std_out, "dup2");
		ft_clean_all_child(shell, status);
	}
	close(*std_in);
	close(*std_out);
	if (right->type == AST_CMD)
		status = ft_exec_cmd_pipe(right, shell);
	else
		status = ft_exec_in_pipe(right, shell);
	ft_clean_all_child(shell, status);
}

int	ft_exec_cmd_pipe(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (OK);
	if (ft_apply_redir(ast, shell) == ERROR)
	{
		if (shell->last_exit_code == 130)
			return (130);
		return (ERROR);
	}
	if (ft_sig_init(SIGINT, SIG_DFL, 0) == ERROR)
		ft_clean_all_child(shell, ERROR);
	if (ft_sig_init(SIGQUIT, SIG_DFL, 0) == ERROR)
		ft_clean_all_child(shell, ERROR);
	if (!ast->args || !ast->args[0])
		return (OK);
	if (ft_is_builtin(ast->args[0]) == 1)
		return (ft_exec_built(ast, &shell->build_env, shell, NULL));
	ft_execve(ast, shell);
	return (OK);
}
