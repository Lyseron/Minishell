/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:47:23 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/31 19:47:23 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

void	ft_handler_exec(int signal)
{
	g_sig_received = signal;
	if (g_sig_received == SIGINT)
		write(1, "\n", 1);
}

void	ft_handler(int signal)
{
	g_sig_received = signal;
	if (g_sig_received == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handler_heredoc_child(int signal)
{
	g_sig_received = signal;
	if (g_sig_received == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	ft_sig_readline_parent(t_shell *shell)
{
	if (g_sig_received == SIGINT)
	{
		g_sig_received = 0;
		shell->last_exit_code = 130;
	}
}

int	ft_sig_init(int sig, void (*handler_func)(int), int flags)
{
	struct sigaction	sa;

	sa.sa_handler = handler_func;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	if (sigaction(sig, &sa, NULL) == -1)
		return (ERROR);
	return (OK);
}
