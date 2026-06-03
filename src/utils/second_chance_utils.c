/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_chance_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 03:25:17 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/07 03:25:17 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_second_chance(t_sec *s)
{
	s->pid = 0;
	s->reading = 0;
	s->writing = 0;
	s->status = 0;
	s->all_line = NULL;
	s->bytes_read = 0;
}

int	ft_clean_second_chance(t_shell *shell, t_sec *s)
{
	if (s->status == 130)
		return (free(s->all_line), shell->last_exit_code = 130, ERROR);
	else if (s->status != OK)
		return (free(s->all_line), shell->last_exit_code = s->status, ERROR);
	if (s->bytes_read <= 0)
		return (free(s->all_line), ERROR);
	return (OK);
}

void	ft_free_some(char **line, char **next_line, int *wri)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	if (next_line && *next_line)
	{
		free(*next_line);
		*next_line = NULL;
	}
	if (wri && *wri != -1)
	{
		close(*wri);
		*wri = -1;
	}
}

void	ft_null_next_line(char **line, int *wri, t_shell *shell)
{
	ft_print_err_msg("syntax error", "unexpected end of file");
	ft_free_some(line, NULL, wri);
	ft_clean_all_child(shell, 1);
}

void	ft_end_second_chance(char **line, int *writing)
{
	write(*writing, *line, ft_strlen(*line) + 1);
	free(*line);
	close(*writing);
}
