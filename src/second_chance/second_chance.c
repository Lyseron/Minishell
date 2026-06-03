/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_chance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:07:29 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/26 22:07:29 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_needs_more(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_iswhitespace(line[i]) == 1)
		i--;
	if (i < 0 || line[i] != '|')
		return (0);
	i--;
	while (i >= 0 && ft_iswhitespace(line[i]) == 1)
		i--;
	if (i < 0)
		return (0);
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (0);
	return (1);
}

void	ft_handler_second_chance(int signal)
{
	g_sig_received = signal;
	if (g_sig_received == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

int	ft_i_sc_child(char **next_line, char **concat_line, int *reading)
{
	*next_line = NULL;
	*concat_line = NULL;
	close(*reading);
	if (ft_sig_init(SIGINT, ft_handler_second_chance, 0) == ERROR)
		return (ERROR);
	return (OK);
}

void	ft_sc_child(char *line, int reading, int w, t_shell *shell)
{
	char	*next_line;
	char	*concat_line;

	if (ft_i_sc_child(&next_line, &concat_line, &reading) == ERROR)
		ft_exit_err_sig(shell, w, &line);
	while (ft_needs_more(line) == 1)
	{
		next_line = readline("> ");
		if (g_sig_received == SIGINT)
		{
			g_sig_received = 0;
			ft_free_some(&line, &next_line, &w);
			ft_clean_all_child(shell, 130);
		}
		if (!next_line)
			ft_null_next_line(&line, &w, shell);
		concat_line = ft_strjoin(line, next_line);
		if (!concat_line)
			ft_exit_sc_child(&line, &next_line, &w, shell);
		free(next_line);
		free(line);
		line = concat_line;
	}
	ft_end_second_chance(&line, &w);
	ft_clean_all_child(shell, OK);
}

char	*ft_second_chance_parent(char *line, t_shell *shell)
{
	t_sec	s;

	ft_init_second_chance(&s);
	if (ft_create_pipe(&s.reading, &s.writing) == ERROR)
		return (free(line), NULL);
	if (ft_sig_init(SIGINT, SIG_IGN, 0) == ERROR)
		return (free(line), close(s.reading), close(s.writing), NULL);
	s.pid = fork();
	if (s.pid == -1)
		return (ft_sig_init(SIGINT, ft_handler, 0),
			free(line), close(s.reading), close(s.writing), NULL);
	else if (s.pid == 0)
		ft_sc_child(line, s.reading, s.writing, shell);
	close(s.writing);
	if (ft_malloc_sc(&s, &line) == ERROR)
		return (ft_sig_init(SIGINT, ft_handler, 0), NULL);
	s.status = ft_wait_cmd(s.pid);
	if (ft_sig_init(SIGINT, ft_handler, 0) == ERROR)
		return (free(line), free(s.all_line), NULL);
	free(line);
	if (ft_clean_second_chance(shell, &s) == ERROR)
		return (NULL);
	return (s.all_line);
}
