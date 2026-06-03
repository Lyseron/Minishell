/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jercleme <jercleme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:19:46 by jercleme          #+#    #+#             */
/*   Updated: 2026/04/01 01:19:46 by jercleme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flags(char *args)
{
	int	i;

	i = 0;
	if (!args || args[0] != '-' || args[1] != 'n')
		return (ERROR);
	while (args[i])
	{
		if (args[i] == '-')
		{
			i++;
			while (args[i] == 'n')
				i++;
		}
		if (ft_strlen(args) == i)
			return (0);
		else
			return (1);
	}
	return (OK);
}

int	ft_builtin_echo(char **args, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	i = 1;
	newline = 1;
	while (args[i] && check_flags(args[i]) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (OK);
}
