/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:25:26 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/01 01:25:26 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_pwd(t_shell *shell)
{
	char	pwd[2000];

	(void)shell;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		return (ft_print_err_msg("pwd", strerror(errno)), ERROR);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (OK);
}
