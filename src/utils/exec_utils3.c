/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 23:48:09 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/26 23:48:09 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_c_h_nocmd(int in_cpy, int out_cpy, t_redir *redir, t_shell *shell)
{
	int	status;

	if (dup2(in_cpy, 0) == -1)
	{
		status = ft_close_fd(&in_cpy, &out_cpy, "dup2");
		ft_clean_all_child(shell, status);
	}
	if (dup2(out_cpy, 1) == -1)
	{
		status = ft_close_fd(&in_cpy, &out_cpy, "dup2");
		ft_clean_all_child(shell, status);
	}
	close(in_cpy);
	close(out_cpy);
	if (ft_sig_init(SIGINT, ft_handler_heredoc_child, 0) == ERROR)
		ft_clean_all_child(shell, ERROR);
	status = ft_exec_heredoc_no_cmd(redir);
	ft_clean_all_child(shell, status);
}

int	ft_cond(t_shell *shell, int in_cpy, int out_cpy, t_redir *redir)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
		ft_c_h_nocmd(in_cpy, out_cpy, redir, shell);
	else
	{
		status = ft_wait_cmd(pid);
		if (status == 130)
			return (shell->last_exit_code = 130, ERROR);
		else if (status == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else
			return (status);
	}
	return (OK);
}

int	ft_no_cmd_clean(int *out_cpy, int *in_cpy)
{
	int	status;

	status = OK;
	if (dup2(*out_cpy, 1) == -1)
		status = ERROR;
	if (dup2(*in_cpy, 0) == -1)
		status = ERROR;
	close(*in_cpy);
	close(*out_cpy);
	return (status);
}

int	ft_no_cmd_but_redir(t_ast *ast, t_shell *shell)
{
	int		out_cpy;
	int		in_cpy;

	if (ast->redirs)
	{
		out_cpy = dup(1);
		if (out_cpy == -1)
			return (ERROR);
		in_cpy = dup(0);
		if (in_cpy == -1)
			return (close(out_cpy), ERROR);
		if (ft_aply_no_c(ast, shell, out_cpy, in_cpy) == ERROR)
			return (ft_no_cmd_clean(&out_cpy, &in_cpy), ERROR);
		if (ft_no_cmd_clean(&out_cpy, &in_cpy) == ERROR)
			return (ERROR);
	}
	return (OK);
}
