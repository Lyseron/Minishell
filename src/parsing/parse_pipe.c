/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 06:43:59 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/20 06:43:59 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// construct the left and right by looking what top one is next
// start == pipe -> nothing to the left
// pipe->next == stop -> nothing to the right
t_ast	*ft_parse_pipe(t_token *start, t_token *stop, t_token *pipe)
{
	t_ast	*pipe_node;

	if (start == pipe || pipe->next == stop)
		return (NULL);
	pipe_node = ft_lstnew_type_ast(AST_PIPE);
	if (!pipe_node)
		return (ft_free_ast(pipe_node), NULL);
	pipe_node->left = ft_parse(start, pipe);
	if (!pipe_node->left)
		return (ft_free_ast(pipe_node), NULL);
	pipe_node->right = ft_parse(pipe->next, stop);
	if (!pipe_node->right)
		return (ft_free_ast(pipe_node), NULL);
	return (pipe_node);
}
