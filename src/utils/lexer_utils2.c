/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_chain_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:35:42 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/18 21:35:42 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to get the last node in a link chained
t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// create a node with a enum type
t_token	*ft_lstnew_type(char *content, t_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

// add one node to the back of the list
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

// free the link chaine
void	ft_lstfree(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		if (head->content)
			free(head->content);
		if (head)
			free(head);
		head = tmp;
	}
}

// to malloc the content of a token
// and add the word to the link chaine
// and moove i twice for the << or >>
void	ft_lexer_a_and_h(t_token **tokens, int *i, char *s, t_type type)
{
	char	*word;
	t_token	*new;

	word = ft_strdup(s);
	new = ft_lstnew_type(word, type);
	ft_lstadd_back(tokens, new);
	(*i)++;
	(*i)++;
}
