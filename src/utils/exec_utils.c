/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:01:06 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/24 15:01:06 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create the pipe 3 and 4
// to after be dup2 with the existing one stdin = 0 / stdout = 1
int	ft_create_pipe(int *std_r, int *std_w)
{
	int	std[2];

	if (pipe(std) == -1)
		return (1);
	*std_r = std[0];
	*std_w = std[1];
	return (OK);
}

// handle the error msg and exit for the fail path
void	ft_exit(int *status, t_ast *ast, t_shell *shell)
{
	if (*status == 127)
	{
		ft_print_err_msg(ast->args[0], "command not found");
		ft_clean_all_child(shell, 127);
	}
	else if (*status == 126)
	{
		ft_print_err_msg(ast->args[0], strerror(errno));
		ft_clean_all_child(shell, 126);
	}
	else if (*status == 1)
		ft_clean_all_child(shell, 1);
}

int	ft_close_fd(int *std_r, int *std_w, char *msg)
{
	if (std_r && *std_r != -1)
	{
		close(*std_r);
		*std_r = -1;
	}
	if (std_w && *std_w != -1)
	{
		close(*std_w);
		*std_w = -1;
	}
	if (msg)
		ft_print_err_msg(NULL, msg);
	return (ERROR);
}

void	ft_exit_slash(int *status, t_ast *ast, t_shell *shell)
{
	if (errno == ENOTDIR)
		ft_exit_enotdir(ast, shell);
	if (*status == 127)
	{
		ft_print_err_msg(ast->args[0], strerror(errno));
		ft_clean_all_child(shell, 127);
	}
	else if (*status == 126 && ft_is_a_directory(ast->args[0]) == 1)
	{
		ft_print_err_msg(ast->args[0], "is a directory");
		ft_clean_all_child(shell, 126);
	}
	else if (*status == 126)
	{
		ft_print_err_msg(ast->args[0], "Permission denied");
		ft_clean_all_child(shell, 126);
	}
	else if (*status == 1)
		ft_clean_all_child(shell, 1);
}
