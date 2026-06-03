/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:27:28 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/31 17:27:28 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_type_to_str(t_token *token)
{
	if (token == NULL)
		return ("newline");
	else if (token->type == PIPE)
		return ("|");
	else if (token->type == REDIR_OUT)
		return (">");
	else if (token->type == REDIR_IN)
		return ("<");
	else if (token->type == APPEND)
		return (">>");
	else if (token->type == HEREDOC)
		return ("<<");
	else
		return (NULL);
}

int	ft_error_input_pipe(t_token *token)
{
	if (token->next && (token->type != WORD && token->next->type == PIPE))
		return (ft_print_error(token->next));
	else
		return (OK);
}

int	ft_error_input_redir(t_token *token)
{
	if (ft_is_redir(token) == 1 && token->next == NULL)
		return (ft_print_error(NULL));
	if (token->next && (ft_is_redir(token) == 1
			&& token->next->type != WORD))
		return (ft_print_error(token->next));
	return (OK);
}

int	ft_error_input_else(t_token *token)
{
	if (token->type == NONO_CHAR)
		return (ft_print_error(NULL));
	else
		return (OK);
}
