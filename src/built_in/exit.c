/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:08:07 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/01 01:08:07 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_change_sign(t_atoi *a, char *s)
{
	if (s[a->i] == '-' || s[a->i] == '+')
	{
		if (s[a->i] == '-')
			a->sign = a->sign * -1;
		a->i++;
	}
}

long long	ft_overflow(t_close *c, t_shell *shell)
{
	ft_print_err_msg_spe(shell->ast->args[0], "numeric argument required",
		shell->ast->args[1]);
	if (c)
	{
		close(c->in);
		close(c->out);
	}
	ft_clean_all_child(shell, 2);
	return (INVALID_INPUT);
}

static long long	ft_atoi_check_overflow(char *s, t_shell *shell, t_close *c)
{
	t_atoi	a;

	ft_init_atoi(&a);
	while (ft_iswhitespace(s[a.i]) == 1)
		a.i++;
	ft_change_sign(&a, s);
	if (a.sign == -1)
		a.overflow = (unsigned long long)LLONG_MAX + 1;
	else
		a.overflow = (unsigned long long)LLONG_MAX;
	while (ft_isdigit(s[a.i]) == 1)
	{
		a.nb = s[a.i] - '0';
		if (a.result > (a.overflow - a.nb) / 10)
			return (ft_overflow(c, shell));
		a.result = a.result * 10 + a.nb;
		a.i++;
	}
	if (a.sign == -1 && a.result == (unsigned long long)LLONG_MAX + 1)
		return (LLONG_MIN);
	return ((long long)a.result * a.sign);
}

static int	ft_exit_code_check(char **args)
{
	int	i;

	if (!args[1])
		return (OK);
	i = 0;
	if (args[1][i] == '+' || args[1][i] == '-')
		i++;
	if (!args[1][i])
		return (ft_print_err_msg_spe(args[0], "numeric argument required",
				args[1]), INVALID_INPUT);
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]) != 1)
			return (ft_print_err_msg_spe(args[0], "numeric argument required",
					args[1]), INVALID_INPUT);
		i++;
	}
	if (args[2] != NULL)
		return (ft_print_err_msg(args[0], "too many arguments"), ERROR);
	return (OK);
}

int	ft_builtin_exit(char **args, t_shell *shell, t_close *c)
{
	int	exit_code;
	int	error;

	write(2, "exit\n", 5);
	exit_code = shell->last_exit_code % 256;
	if (args[1])
	{
		error = ft_exit_code_check(args);
		if (error == INVALID_INPUT)
			exit_code = INVALID_INPUT;
		else if (error == ERROR)
			return (ERROR);
		else
			exit_code = ft_atoi_check_overflow(args[1], shell, c) % 256;
	}
	shell->last_exit_code = exit_code;
	if (shell->in_pipe == true)
		ft_clean_all_child(shell, exit_code);
	shell->exit = true;
	return (exit_code);
}
