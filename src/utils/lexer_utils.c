/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:36:12 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/18 21:36:12 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concate each char send to create a word
char	*ft_add_each_char(char *word, char c)
{
	int		i;
	char	*new_word;
	int		len;

	i = 0;
	if (!word)
		return (NULL);
	len = ft_strlen(word);
	if (len == -1)
		return (free(word), word = NULL, NULL);
	new_word = malloc(sizeof(char) * (len + 2));
	if (!new_word)
		return (free(word), NULL);
	while (word[i])
	{
		new_word[i] = word[i];
		i++;
	}
	new_word[i] = c;
	new_word[i + 1] = '\0';
	free(word);
	return (new_word);
}

// look after the ' or " and concate each char til the next ' or "
// advance the i after the '
// word start empty(or with the string to concate) than get
// filled with each char til the char c
// return the created word (everything in the char c)
static char	*ft_create_word(char *line, char *word, int *i, char c)
{
	word = ft_add_each_char(word, line[*i]);
	if (!word)
		return (NULL);
	(*i)++;
	while (line[*i] && line[*i] != c)
	{
		word = ft_add_each_char(word, line[*i]);
		if (!word)
			return (NULL);
		(*i)++;
	}
	if (line[*i] == c)
	{
		word = ft_add_each_char(word, line[*i]);
		if (!word)
			return (NULL);
		(*i)++;
	}
	return (word);
}

static int	ft_end_lexer_word(char *word, t_token **tokens)
{
	t_token	*new;

	new = ft_lstnew_type(word, WORD);
	if (!new)
	{
		free(word);
		return (ERROR);
	}
	ft_lstadd_back(tokens, new);
	return (OK);
}

// the loop stop when there is a whitespace or a < > |
// if there is a quote
// the line is send to create word the take everything 
// inside the quote to make it 1 token
// else it create a word with all the char til the whitespace of the < > |
// i -> is updated every time
void	ft_lexer_word(t_token **tokens, int *i, char *line)
{
	char	*word;

	word = ft_strdup("");
	if (!word)
		return ;
	while (line[*i] && !ft_iswhitespace(line[*i]) && !ft_is_spe_char(line[*i]))
	{
		if (line[*i] == SQ)
			word = ft_create_word(line, word, i, SQ);
		else if (line[*i] == DQ)
			word = ft_create_word(line, word, i, DQ);
		else
		{
			word = ft_add_each_char(word, line[*i]);
			if (!word)
				return ;
			(*i)++;
		}
		if (!word)
			return ;
	}
	if (ft_end_lexer_word(word, tokens) == ERROR)
		return ;
}

// to malloc the content of a token 
// and add the word to the link chaine
// and moove i for the < or > or |
void	ft_lexer_spe_char(t_token **tokens, int *i, char *s, t_type type)
{
	char	*word;
	t_token	*new;

	if (!s || !tokens)
		return ;
	word = ft_strdup(s);
	if (!word)
		return ;
	new = ft_lstnew_type(word, type);
	ft_lstadd_back(tokens, new);
	(*i)++;
}
