/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:40:01 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/29 19:40:01 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reset_std(int std_in, t_redir *redir)
{
	if (redir->next && (redir->next->type_redir == APPEND
			|| redir->next->type_redir == REDIR_OUT))
	{
		if (dup2(std_in, 0) == -1)
			return (close(std_in), ERROR);
	}
	else if (!redir->next)
	{
		if (dup2(std_in, 0) == -1)
			return (close(std_in), ERROR);
	}
	return (OK);
}

int	ft_norminette(t_exec_heredoc *e)
{
	if (dup2(e->tty_in, 0) == -1 || dup2(e->tty_out, 1) == -1)
		return (close(e->std_in), close(e->std_out), close(e->save_in),
			close(e->save_out), close(e->tty_in), close(e->tty_out), ERROR);
	return (OK);
}

int	ft_loop_heredoc(t_exec_heredoc *e, t_shell *shell, t_redir *redir)
{
	while (1)
	{
		if (ft_norminette(e) == ERROR)
			return (ERROR);
		e->line = readline("> ");
		if (g_sig_received == SIGINT)
			return (ft_for_sigint_heredoc(e, shell));
		if (!e->line)
		{
			ft_print_err_msg_heredoc(redir->heredoc_eof);
			break ;
		}
		else if (ft_strcmp(e->line, redir->heredoc_eof) == 0)
		{
			free(e->line);
			break ;
		}
		else
			ft_exp_h(&e->line, e->std_out, redir, shell);
	}
	return (OK);
}
