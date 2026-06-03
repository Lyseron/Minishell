/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:23:10 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/26 12:23:10 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle the error of execve
void	ft_error_execve(char *path_cmd, t_ast *ast, t_shell *shell)
{
	(void)ast;
	ft_print_err_msg(path_cmd, strerror(errno));
	if (path_cmd)
	{
		free(path_cmd);
		path_cmd = NULL;
	}
	ft_clean_all_child(shell, ERROR);
}

int	ft_wait_no_eintr(pid_t pid, int *status)
{
	int	stat;

	stat = waitpid(pid, status, 0);
	while (stat == -1 && errno == EINTR)
		stat = waitpid(pid, status, 0);
	if (stat == -1)
		return (ERROR);
	return (OK);
}

static int	ft_wait_sigint(pid_t pid_out, int *status_out)
{
	kill(pid_out, SIGINT);
	ft_wait_no_eintr(pid_out, status_out);
	return (130);
}

// wait for cmd1 and cmd2 to avoid zombies
// check the exit code for cmd2 and return the right exit
int	ft_wait(pid_t pid_in, pid_t pid_out)
{
	int	status_in;
	int	status_out;
	int	code_exit;

	if (ft_wait_no_eintr(pid_in, &status_in) == ERROR)
		return (1);
	if (WIFSIGNALED(status_in) && WTERMSIG(status_in) == SIGINT)
		return (ft_wait_sigint(pid_out, &status_out));
	if (WIFEXITED(status_in) && WEXITSTATUS(status_in) == 130)
		return (ft_wait_sigint(pid_out, &status_out));
	if (ft_wait_no_eintr(pid_out, &status_out) == ERROR)
		return (1);
	if (WIFEXITED(status_out) == 1)
		code_exit = WEXITSTATUS(status_out);
	else if (WIFSIGNALED(status_out) == 1)
		code_exit = 128 + WTERMSIG(status_out);
	else
		code_exit = 1;
	return (code_exit);
}

int	ft_wait_cmd(pid_t pid)
{
	int	status;
	int	code_exit;

	if (ft_wait_no_eintr(pid, &status) == ERROR)
		return (ERROR);
	if (WIFEXITED(status))
		code_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		code_exit = 128 + WTERMSIG(status);
	else
		code_exit = 1;
	return (code_exit);
}
