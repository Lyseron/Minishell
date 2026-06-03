/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:10:08 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/26 12:10:08 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_redir_out(t_redir *redir)
{
	int		fd;

	if (!redir)
		return (ERROR);
	fd = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, 1) == -1)
		return (close(fd), ERROR);
	close(fd);
	return (OK);
}

int	ft_exec_redir_in(t_redir *redir)
{
	int	fd;

	if (!redir)
		return (ERROR);
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, 0) == -1)
		return (close(fd), ERROR);
	close(fd);
	return (OK);
}

int	ft_exec_append(t_redir *redir)
{
	int	fd;

	if (!redir)
		return (ERROR);
	fd = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (ERROR);
	if (dup2(fd, 1) == -1)
		return (close(fd), ERROR);
	close(fd);
	return (OK);
}

// the damn pipe has a damn memory to store data til
// the content is not read!
int	ft_exec_heredoc(t_redir *redir, t_shell *shell)
{
	t_exec_heredoc	e;

	if (ft_begin_exec_heredoc(&e, redir) == ERROR)
		return (ERROR);
	if (ft_loop_heredoc(&e, shell, redir) == ERROR)
		return (ERROR);
	if (ft_end_exec_heredoc(&e, redir) == ERROR)
		return (ERROR);
	return (OK);
}

int	ft_exec_heredoc_no_cmd(t_redir *redir)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (g_sig_received == SIGINT)
		{
			free(line);
			g_sig_received = 0;
			return (130);
		}
		if (!line)
			break ;
		else if (ft_strcmp(line, redir->heredoc_eof) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (OK);
}
