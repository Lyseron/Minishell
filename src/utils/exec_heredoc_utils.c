/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:51 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/29 19:40:51 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_for_sigint_heredoc(t_exec_heredoc *e, t_shell *shell)
{
	free(e->line);
	close(e->std_out);
	close(e->std_in);
	if (dup2(e->save_in, STDIN_FILENO) == -1
		|| dup2(e->save_out, STDOUT_FILENO) == -1)
		return (close(e->save_in), close(e->save_out),
			close(e->tty_in), close(e->tty_out), ERROR);
	close(e->save_in);
	close(e->save_out);
	close(e->tty_in);
	close(e->tty_out);
	shell->last_exit_code = 130;
	g_sig_received = 0;
	return (ERROR);
}

void	ft_init_exec_heredoc(t_exec_heredoc *e)
{
	e->line = NULL;
	e->std_out = -1;
	e->std_in = -1;
	e->save_in = -1;
	e->save_out = -1;
	e->tty_in = -1;
	e->tty_out = -1;
}

int	ft_error_fd(t_exec_heredoc *e)
{
	e->save_in = dup(0);
	if (e->save_in == -1)
		return (close(e->std_in), close(e->std_out), ERROR);
	e->save_out = dup(1);
	if (e->save_out == -1)
		return (close(e->std_in), close(e->std_out),
			close(e->save_in), ERROR);
	e->tty_in = open("/dev/tty", O_RDONLY);
	if (e->tty_in == -1)
		return (close(e->std_in), close(e->std_out),
			close(e->save_in), close(e->save_out), ERROR);
	e->tty_out = open("/dev/tty", O_WRONLY);
	if (e->tty_out == -1)
		return (close(e->std_in), close(e->std_out),
			close(e->save_in), close(e->save_out), close(e->tty_in), ERROR);
	return (OK);
}

int	ft_end_exec_heredoc(t_exec_heredoc *e, t_redir *redir)
{
	if (dup2(e->save_in, 0) == -1 || dup2(e->save_out, 1) == -1)
		return (close(e->save_in), close(e->save_out),
			close(e->tty_in), close(e->tty_out), ERROR);
	close(e->save_in);
	close(e->save_out);
	close(e->tty_in);
	close(e->tty_out);
	close(e->std_out);
	if (ft_reset_std(e->std_in, redir) == ERROR)
		return (ERROR);
	close(e->std_in);
	return (OK);
}

int	ft_begin_exec_heredoc(t_exec_heredoc *e, t_redir *redir)
{
	ft_init_exec_heredoc(e);
	if (!redir || ft_create_pipe(&e->std_in, &e->std_out) == 1)
		return (ERROR);
	if (ft_error_fd(e) == ERROR)
		return (ERROR);
	return (OK);
}
