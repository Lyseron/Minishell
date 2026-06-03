/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:52:23 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/20 09:52:23 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast		*ft_parse(t_token *start, t_token *stop);
static int	ft_parse_error(t_token *token);

int	ft_parsing_check(t_token **tokens, t_ast **ast, t_shell *shell)
{
	if (!*tokens || !tokens)
		return (ERROR);
	if (ft_parse_error(*tokens) == INVALID_INPUT)
		return (INVALID_INPUT);
	*ast = ft_parse(*tokens, NULL);
	if (!*ast)
		return (shell->last_exit_code = 2, ERROR);
	return (OK);
}

// rederect the tree depending on the input
t_ast	*ft_parse(t_token *start, t_token *stop)
{
	t_token		*pipe;

	pipe = ft_foundlast_pipe(start, stop);
	if (pipe)
		return (ft_parse_pipe(start, stop, pipe));
	return (ft_parse_cmd(start, stop));
}

static int	ft_parse_error(t_token *token)
{
	t_token	*head;

	if (!token)
		return (1);
	head = token;
	if (head->type == PIPE)
		return (ft_print_error(token));
	else if (ft_strcmp(head->content, ".") == 0 && !head->next)
		return (ft_print_err_msg(".", "filename argument required"),
			INVALID_INPUT);
	while (token)
	{
		if (ft_error_input_pipe(token) == INVALID_INPUT)
			return (INVALID_INPUT);
		if (ft_error_input_redir(token) == INVALID_INPUT)
			return (INVALID_INPUT);
		if (ft_error_input_else(token) == INVALID_INPUT)
			return (INVALID_INPUT);
		token = token->next;
	}
	return (OK);
}

char	*ft_rm_eof_q(char *eof)
{
	char	*no_q_eof;
	int		i;
	int		j;

	no_q_eof = malloc(sizeof(char) * (ft_strlen(eof) + 1));
	if (!no_q_eof)
		return (NULL);
	i = 0;
	j = 0;
	while (eof && eof[i])
	{
		if (eof[i] != '\"' && eof[i] != '\'')
			no_q_eof[j++] = eof[i];
		i++;
	}
	no_q_eof[j] = '\0';
	return (no_q_eof);
}
