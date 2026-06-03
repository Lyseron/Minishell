/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:50:38 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/24 20:50:38 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_status_child(pid_t pid);

int	ft_exec_cmd(t_ast *ast, t_shell *shell)
{
	pid_t	pid;

	if (!ast)
		return (OK);
	if (!ast->args || !ast->args[0])
	{
		if (ft_no_cmd_but_redir(ast, shell) == ERROR)
			return (ERROR);
		return (OK);
	}
	if (ft_strcmp(ast->args[0], "env") == 0 && ast->args[1])
		return (ft_env_with_smt(ast, shell));
	else if (ft_is_builtin(ast->args[0]) == 1)
		return (ft_builtin(ast, shell));
	else
	{
		pid = fork();
		if (pid == -1)
			return (ERROR);
		else if (pid == 0)
			ft_exec_cmd_child(ast, shell);
	}
	return (ft_status_child(pid));
}

int	ft_status_child(pid_t pid)
{
	int	status;

	status = ft_wait_cmd(pid);
	if (status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	return (status);
}

void	ft_exec_cmd_child(t_ast *ast, t_shell *shell)
{
	if (!ast || !ast->args || !ast->args[0])
		ft_clean_all_child(shell, OK);
	if (ft_sig_init(SIGINT, ft_handler_heredoc_child, 0) == ERROR)
		ft_clean_all_child(shell, ERROR);
	if (ft_apply_redir(ast, shell) == ERROR)
	{
		if (shell->last_exit_code == 130)
			ft_clean_all_child(shell, 130);
		ft_clean_all_child(shell, ERROR);
	}
	if (ft_sig_init(SIGINT, SIG_DFL, 0) == ERROR)
		ft_clean_all_child(shell, ERROR);
	if (ft_sig_init(SIGQUIT, SIG_DFL, 0) == ERROR)
		ft_clean_all_child(shell, ERROR);
	ft_execve(ast, shell);
	ft_clean_all_child(shell, ERROR);
}

void	ft_execve(t_ast *ast, t_shell *shell)
{
	char	*path_cmd;
	int		status;

	if (!ast || !ast->args || !ast->args[0])
		return ;
	path_cmd = ft_test_path(ft_extract_p(shell->build_env),
			ast->args[0], &status);
	if (ft_contain_slash(ast->args[0]) == 1)
		ft_exit_slash(&status, ast, shell);
	else
		ft_exit(&status, ast, shell);
	if (status == 0 && path_cmd != NULL)
		execve(path_cmd, ast->args, shell->build_env);
	ft_error_execve(path_cmd, ast, shell);
}
