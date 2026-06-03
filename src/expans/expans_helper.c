/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expans_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 00:05:56 by lyaberge          #+#    #+#             */
/*   Updated: 2026/04/27 00:05:56 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_state(char c, t_qstate *state, int *i)
{
	if (ft_is_quote(c, *state) == 1)
	{
		ft_change_state(c, state);
		(*i)++;
		return (1);
	}
	return (0);
}

char	*ft_dollar(char *new, char *line, int *i, t_shell *shell)
{
	if (line[*i + 1] && line[*i + 1] == '?')
		return (ft_string_exit_code(new, i, shell));
	else if (line[*i + 1] && (line[*i + 1] == '_'
			|| ft_isalpha(line[*i + 1])))
		return (ft_add_str(new, line, i, shell));
	else if (line[*i + 1] && ft_isdigit(line[*i + 1]))
	{
		*i = *i + 2;
		return (new);
	}
	else
	{
		new = ft_add_each_char(new, line[*i]);
		if (!new)
			return (NULL);
		(*i)++;
	}
	return (new);
}

void	ft_init_expand(int *i, t_qstate *state)
{
	*i = 0;
	*state = NO_Q;
}

void	ft_free_vars(char **var, char **var_content, char **word)
{
	if (*var)
		free(*var);
	if (*var_content)
		free(*var_content);
	if (*word)
		free(*word);
}

int	ft_handle_args(t_ast *ast, t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*arg;
	bool	has_quote;

	i = 0;
	while (ast && ast->args && ast->args[i])
	{
		tmp = ast->args[i];
		has_quote = ft_has_quote(tmp);
		arg = ft_expand(ast->args[i], shell);
		if (!arg)
			return (ERROR);
		ast->args[i] = arg;
		free(tmp);
		if (arg[0] == '\0' && has_quote == false)
			ft_remove_empty_arg(ast->args, i);
		else
			i++;
	}
	return (OK);
}
