/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:53:09 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/04 19:53:09 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_close(t_close *c, int std_in, int std_out)
{
	c->in = std_in;
	c->out = std_out;
}

//dup(1) && dup(2) to save the original fd and
// put it back at the end of the execution
int	ft_builtin(t_ast *ast, t_shell *shell)
{
	t_close		c;
	int			std_out;
	int			std_in;
	int			exit_code;

	exit_code = ERROR;
	std_out = dup(STDOUT_FILENO);
	if (std_out == -1)
		return (ERROR);
	std_in = dup(STDIN_FILENO);
	if (std_in == -1)
		return (close(std_out), ERROR);
	ft_init_close(&c, std_in, std_out);
	if (ft_aply_no_c(ast, shell, std_out, std_in) != ERROR)
		exit_code = ft_exec_built(ast, &shell->build_env, shell, &c);
	if (dup2(std_out, STDOUT_FILENO) == -1)
		return (close(std_in), close(std_out), ERROR);
	if (dup2(std_in, STDIN_FILENO) == -1)
		return (close(std_in), close(std_out), ERROR);
	close(std_out);
	close(std_in);
	return (exit_code);
}
