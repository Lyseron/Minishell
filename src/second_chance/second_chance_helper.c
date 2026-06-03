/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_chance_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 22:29:43 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/28 22:29:43 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_sc_child(char **line, char **n_l, int *w, t_shell *shell)
{
	ft_free_some(line, n_l, w);
	ft_clean_all_child(shell, 1);
}

int	ft_malloc_sc(t_sec *s, char **line)
{
	s->all_line = malloc(5001);
	if (!s->all_line)
		return (free(*line), close(s->reading), ERROR);
	s->bytes_read = read(s->reading, s->all_line, 5000);
	close(s->reading);
	if (s->bytes_read < 0)
		return (free(*line), free(s->all_line), ERROR);
	s->all_line[s->bytes_read] = '\0';
	return (OK);
}

void	ft_exit_err_sig(t_shell *shell, int w, char **line)
{
	close(w);
	free(*line);
	ft_clean_all_child(shell, ERROR);
}
