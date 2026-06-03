/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expans.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:10:56 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/12 14:10:56 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_normal_char(int *i, char *new, char *line)
{
	new = ft_add_each_char(new, line[*i]);
	if (!new)
		return (NULL);
	(*i)++;
	return (new);
}

char	*ft_expand(char *line, t_shell *shell)
{
	char		*new;
	int			i;
	t_qstate	state;

	new = ft_strdup("");
	if (!new)
		return (NULL);
	ft_init_expand(&i, &state);
	while (line && line[i])
	{
		if (ft_quote_state(line[i], &state, &i) == 1)
			continue ;
		if (line[i] == '$' && state != SQUOTE)
		{
			new = ft_dollar(new, line, &i, shell);
			if (!new)
				return (NULL);
		}
		else
			new = ft_normal_char(&i, new, line);
		if (!new)
			return (NULL);
	}
	return (new);
}

int	ft_conditions(char *line, int *i, char **new, t_shell *shell)
{
	if (line[*i] == '$')
	{
		if (line[*i + 1] && line[*i + 1] == '?')
		{
			*new = ft_string_exit_code(*new, i, shell);
			if (!*new)
				return (ERROR);
		}
		else
		{
			*new = ft_add_str(*new, line, i, shell);
			if (!*new)
				return (ERROR);
		}
	}
	else
	{
		*new = ft_add_each_char(*new, line[*i]);
		if (!*new)
			return (ERROR);
		(*i)++;
	}
	return (OK);
}

char	*ft_expand_line_heredoc(char *line, t_shell *shell)
{
	char		*new;
	int			i;

	new = ft_strdup("");
	if (!new)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		if (ft_conditions(line, &i, &new, shell) == ERROR)
			return (NULL);
	}
	return (new);
}

void	ft_exp_h(char **line, int std_out, t_redir *redir, t_shell *shell)
{
	char	*expand_line;

	if (redir->expand == true)
	{
		expand_line = ft_expand_line_heredoc(*line, shell);
		if (!expand_line)
		{
			free(*line);
			return ;
		}
		ft_write_line(&expand_line, std_out);
	}
	else
		ft_write_line(line, std_out);
}
