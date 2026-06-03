/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:42:03 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/30 10:42:03 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return the last occurence of a redir in the input
t_token	*ft_foundlast_redirs(t_token *start, t_token *stop)
{
	t_token	*last;

	if (!start)
		return (NULL);
	last = NULL;
	while (start != stop)
	{
		if (start->type == REDIR_IN || start->type == REDIR_OUT
			|| start->type == APPEND || start->type == HEREDOC)
			last = start;
		start = start->next;
	}
	return (last);
}

// to get the last node in a link chained
t_redir	*ft_lstlast_redir(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// add one node to the back of the list
void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_redir(*lst);
	last->next = new;
}

// free the link chaine
void	ft_lstfree_redir(t_redir *head)
{
	t_redir	*next;

	if (!head)
		return ;
	while (head)
	{
		next = head->next;
		if (head->file)
			free(head->file);
		if (head->heredoc_eof)
			free(head->heredoc_eof);
		if (head)
			free(head);
		head = next;
	}
}

int	ft_has_no_quote(char *s)
{
	int	i;
	int	found_d;
	int	found_s;

	i = 0;
	found_d = 0;
	found_s = 0;
	while (s && s[i])
	{
		if (s[i] == '\"')
			found_d = found_d + 1;
		if (s[i] == '\'')
			found_s = found_s + 1;
		i++;
	}
	if (found_d >= 2 || found_s >= 2)
		return (0);
	return (1);
}
