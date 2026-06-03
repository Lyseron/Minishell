/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:50:21 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/04 19:50:21 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_choice(t_redir *redir, t_shell *shell)
{
	if (redir->type_redir == REDIR_OUT)
	{
		if (ft_exec_redir_out(redir) == ERROR)
			return (ERROR);
	}
	else if (redir->type_redir == REDIR_IN)
	{
		if (ft_exec_redir_in(redir) == ERROR)
			return (ERROR);
	}
	else if (redir->type_redir == HEREDOC)
	{
		if (ft_exec_heredoc(redir, shell) == ERROR)
			return (ERROR);
	}
	else if (redir->type_redir == APPEND)
	{
		if (ft_exec_append(redir) == ERROR)
			return (ERROR);
	}
	return (OK);
}

int	ft_apply_redir(t_ast *ast, t_shell *shell)
{
	t_redir	*redir;

	redir = ast->redirs;
	while (redir)
	{
		if (ft_redir_choice(redir, shell) == ERROR)
		{
			if (shell->last_exit_code == 130)
				return (ERROR);
			ft_print_err_msg(redir->file, strerror(errno));
			return (ERROR);
		}
		redir = redir->next;
	}
	return (OK);
}

int	ft_aply_no_c(t_ast *ast, t_shell *shell, int out_cpy, int in_cpy)
{
	t_redir	*redir;

	redir = ast->redirs;
	while (redir)
	{
		if (ft_no_c(redir, shell, out_cpy, in_cpy) == ERROR)
		{
			if (shell->last_exit_code == 130)
				return (ERROR);
			else
				ft_print_err_msg(redir->file, strerror(errno));
			return (ERROR);
		}
		redir = redir->next;
	}
	return (OK);
}

int	ft_no_c(t_redir *redir, t_shell *shell, int out_cpy, int in_cpy)
{
	if (redir->type_redir == REDIR_OUT)
	{
		if (ft_exec_redir_out(redir) == ERROR)
			return (ERROR);
	}
	else if (redir->type_redir == REDIR_IN)
	{
		if (ft_exec_redir_in(redir) == ERROR)
			return (ERROR);
	}
	else if (redir->type_redir == HEREDOC)
	{
		if (ft_cond(shell, in_cpy, out_cpy, redir) == ERROR)
			return (ERROR);
	}
	else if (redir->type_redir == APPEND)
	{
		if (ft_exec_append(redir) == ERROR)
			return (ERROR);
	}
	return (OK);
}
