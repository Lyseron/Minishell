/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:53:32 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/20 09:53:32 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_cmd_size_word(t_token *start, t_token *end);
static int		ft_fill_redir(t_token *start, t_ast *cmd, t_type type);
static t_ast	*ft_init_cmd(t_token *start, t_token *stop);

// fonction to sort and fill args/file between start and stop
t_ast	*ft_parse_cmd(t_token *start, t_token *stop)
{
	t_ast	*cmd;
	int		i;

	cmd = ft_init_cmd(start, stop);
	if (!cmd)
		return (ft_free_ast(cmd), NULL);
	i = 0;
	while (start != stop)
	{
		if (start->type == WORD)
		{
			cmd->args[i] = ft_strdup(start->content);
			if (!cmd->args[i])
				return (ft_free_before_i(cmd->args, i), NULL);
			i++;
		}
		else if (start->next && ft_is_redir(start) == 1)
		{
			if (ft_fill_redir(start, cmd, start->type) == 1)
				return (ft_free_ast(cmd), NULL);
			start = start->next;
		}
		start = start->next;
	}
	return (cmd->args[i] = NULL, cmd);
}

static t_ast	*ft_init_cmd(t_token *start, t_token *stop)
{
	t_ast	*cmd;
	int		size;

	size = ft_cmd_size_word(start, stop);
	cmd = ft_lstnew_type_ast(AST_CMD);
	if (!cmd)
		return (ft_free_ast(cmd), NULL);
	cmd->args = malloc(sizeof(char *) * (size + 1));
	if (!cmd->args)
		return (ft_free_ast(cmd), NULL);
	return (cmd);
}

char	*ft_heredoc_eof(char *eof, t_redir *new)
{
	char	*no_q_eof;

	if (!eof)
		return (NULL);
	new->expand = false;
	if (ft_has_no_quote(eof) == 1)
	{
		new->expand = true;
		no_q_eof = ft_strdup(eof);
		if (!no_q_eof)
			return (NULL);
		return (no_q_eof);
	}
	return (ft_rm_eof_q(eof));
}

static int	ft_fill_redir(t_token *start, t_ast *cmd, t_type type)
{
	t_redir	*new;

	new = ft_lstnew_type_redir(type);
	if (!new)
		return (ERROR);
	if (type == HEREDOC)
	{
		new->heredoc_eof = ft_heredoc_eof(start->next->content, new);
		if (!new->heredoc_eof)
			return (free(new), ERROR);
	}
	else
	{
		new->file = ft_strdup(start->next->content);
		if (!new->file)
			return (free(new), ERROR);
	}
	ft_lstadd_back_redir(&cmd->redirs, new);
	return (0);
}

// // size of a chaine list between start and stop
// // only count the word type node
static int	ft_cmd_size_word(t_token *start, t_token *end)
{
	int		size;

	size = 0;
	while (start != end)
	{
		if (start->type == WORD)
			size++;
		start = start->next;
	}
	return (size);
}
