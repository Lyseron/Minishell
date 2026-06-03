/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expans_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:47:23 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/09 08:47:23 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return the content of the variable
char	*ft_return_var_content(t_shell *shell, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (shell->build_env && shell->build_env[i])
	{
		if ((ft_strncmp(shell->build_env[i], var, len) == 0)
			&& shell->build_env[i][len] == '=')
			return (shell->build_env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	ft_len_var(char *var, int i)
{
	int	start;

	start = i;
	if (!var)
		return (-1);
	while (var && var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	return (i - start);
}

void	ft_change_state(char c, t_qstate *state)
{
	if (c == '\'')
	{
		if (*state == NO_Q)
			*state = SQUOTE;
		else if (*state == SQUOTE)
			*state = NO_Q;
	}
	if (c == '\"')
	{
		if (*state == NO_Q)
			*state = DQUOTE;
		else if (*state == DQUOTE)
			*state = NO_Q;
	}
}

int	ft_is_quote(char c, t_qstate state)
{
	if (c == '\'' && state != DQUOTE)
		return (1);
	if (c == '\"' && state != SQUOTE)
		return (1);
	return (0);
}

char	*ft_get_var(char *line, int i)
{
	int		len_var;
	int		j;
	char	*var;

	len_var = ft_len_var(line, i);
	var = malloc(sizeof(char) * (len_var + 1));
	if (!var)
		return (NULL);
	j = 0;
	while (j < len_var)
	{
		var[j] = line[i];
		i++;
		j++;
	}
	var[j] = '\0';
	return (var);
}
