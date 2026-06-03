/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:54:21 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/20 09:54:21 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a new t_ast node
t_ast	*ft_lstnew_type_ast(t_ast_type type)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->args = NULL;
	new_node->redirs = NULL;
	new_node->in_quote = false;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_redir	*ft_lstnew_type_redir(t_type type)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (NULL);
	new_node->type_redir = type;
	new_node->file = NULL;
	new_node->heredoc_eof = NULL;
	new_node->expand = false;
	new_node->next = NULL;
	return (new_node);
}

// return the last occurence of a pipe in the input
t_token	*ft_foundlast_pipe(t_token *start, t_token *stop)
{
	t_token	*last;

	if (!start)
		return (NULL);
	last = NULL;
	while (start != stop)
	{
		if (start->type == PIPE)
			last = start;
		start = start->next;
	}
	return (last);
}

void	ft_free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->right)
		ft_free_ast(ast->right);
	if (ast->left)
		ft_free_ast(ast->left);
	if (ast->args)
		ft_free_dba(ast->args);
	if (ast->redirs)
		ft_lstfree_redir(ast->redirs);
	if (ast)
		free(ast);
}

int	ft_is_redir(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HEREDOC)
		return (1);
	else
		return (0);
}
